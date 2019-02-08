#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg)
{
  perror(msg);
  exit(0);
}

int main(int argc, char *argv[])
{
  int socketfd;
  int portnum;
  int n;
  struct sockaddr_in serveraddr;
  struct hostent *server;

  char buffer[100];

  if (argc < 3)
    error("No host.");

  portnum = atoi(argv[2]);
  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0)
    error("Cannot open socket.");

  server = gethostbyname(argv[1]);
  if (server == NULL)
    error("No such host.");

  bzero((char *) &serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  bcopy((char *)server -> h_addr, (char *)&serveraddr.sin_addr.s_addr, server -> h_length);
  serveraddr.sin_port = htons(portnum);
  if (connect(socketfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)
    error("Cannot connect.");

  printf("Enter message: ");
  bzero(buffer, 100);
  fgets(buffer, 99, stdin);

  n = write(socketfd, buffer, strlen(buffer));
  if (n < 0)
    error("Cannot write to socket");

  bzero(buffer, 100);
  n = read(socketfd, buffer, 99);
  if (n < 0)
    error("Cannot read from socket.");

  printf("Buffer: %s\n", buffer);
  close(socketfd);

  return 0;
}
