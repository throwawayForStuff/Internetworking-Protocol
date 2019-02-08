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

int main()
{
  struct sockaddr_in serveraddr;
  struct sockaddr_in clientaddr;
  bzero(&serveraddr, sizeof(serveraddr));

  int socketfd; //Our socket for storing file descriptor
  int length;
  char buffer[MAX];
  char *message = "Hello World";

  if ((socketfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    perror("Cannot create socket.");
    exit(EXIT_FAILURE);
  }

  //memset(&serveraddr, 0, sizeof(serveraddr));
  //memset(&clientaddr, 0, sizeof(clientaddr));

  /*serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = INADDR_ANY;
  serveraddr.sin_port = htons(PORT);*/

  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(PORT);
  serveraddr.sin_family = AF_INET;

  if (bind(socketfd, (const struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
  {
    perror("Cannot bind.");
    exit(EXIT_FAILURE);
  }

  length = sizeof(clientaddr);
  //n = recvfrom(socketfd, (char *) buffer, MAX, MSG_WAITALL, (struct sockaddr *) &clientaddr, &length);
  int n = recvfrom(socketfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &clientaddr, &length);
  buffer[n] = '\0';

  printf("Client: %s\n", buffer);

  //sendto(socketfd, (const char *)message, strlen(message), MSG_CONFIRM, (const struct sockaddr *) &clientaddr, length);
  sendto(socketfd, message, MAX, 0, (struct sockaddr *)&clientaddr, sizeof(clientaddr));

  printf("Message sent.\n");

  //close(socketfd);

  //return 0;
}

