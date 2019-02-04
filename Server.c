#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 1080
#define MAX  1024

int main(int argc, char const *argv[])
{
  struct sockaddr_in serveraddr;
  struct sockaddr_in clientaddr;

  int socketfd; //Our socket for storing file descriptor
  int length;
  int n;
  char buffer[MAX];
  char *message = "Hello World";
  printf("\nHello World.\n");

  if ((socketfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    perror("Cannot create socket.");
    exit(EXIT_FAILURE);
  }

  memset(&serveraddr, 0, sizeof(serveraddr));
  memset(&clientaddr, 0, sizeof(clientaddr));

  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = INADDR_ANY;
  serveraddr.sin_port = htons(PORT);

  if (bind(socketfd, (const struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
  {
    perror("Cannot bind.");
    exit(EXIT_FAILURE);
  }

  n = recvfrom(socketfd, (char *) buffer, MAX, MSG_WAITALL, (struct sockaddr *) &clientaddr, &length);
  buffer[n] = '\0';

  //Close the socket
  close(socketfd);

  //To create socket, using socket system call
  //int s = (domain, type, protocol);
  

  return 0;
}

