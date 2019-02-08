#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
  perror(msg);
  exit(1);
}

int main(int argc, char *argv[])
{
  int socketfd;
  int newsocketfd;
  int portnum;
  int n;

  socklen_t clilen;

  char buffer[100];
  struct sockaddr_in serveraddr;
  struct sockaddr_in clientaddr;

  if (argc < 2)
    error("No port.");

  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0)
    error("Cannot open socket.");

  bzero((char *) &serveraddr, sizeof(serveraddr));

  portnum = atoi(argv[1]);

  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = INADDR_ANY;
  serveraddr.sin_port = htons(portnum);

  if (bind(socketfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
    error("Cannot bind.");

  listen(socketfd, 5);

  clilen = sizeof(clientaddr);

  newsocketfd = accept(socketfd, (struct sockaddr *) &clientaddr, &clilen);
  if (newsocketfd < 0)
    error("Cannot accept.");

  printf("Server: Got connection from %s port %d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

  send(newsocketfd, "Hello world.\n", 12, 0);

  bzero(buffer, 100);

  n = read(newsocketfd, buffer, 99);
  if (n < 0)
    error("Cannot read from socket.");
  printf("Message: %s\n", buffer);

  close(newsocketfd);
  close(socketfd);
  
  return 0;
}
