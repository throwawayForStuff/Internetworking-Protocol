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

  int socketfd;
  //int length;
  int n;
  char buffer[MAX];
  char *message = "World says hello.";

  bzero(&serveraddr, sizeof(serveraddr));
  //serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  serveraddr.sin_addr.s_addr = INADDR_ANY;
  serveraddr.sin_port = htons(PORT);
  serveraddr.sin_family = AF_INET;

  if ((socketfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    perror("Cannot create socket");
    exit(EXIT_FAILURE);
  }

  if (connect(socketfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
  {
    printf("Cannot connect.");
    exit(0);
  }

  /*memset(&serveraddr, 0, sizeof(serveraddr));

  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = htons(PORT);
  serveraddr.sin_addr.s_addr = INADDR_ANY;*/

  //sendto(socketfd, (const char *)message, strlen(message), MSG_CONFIRM, (const struct sockaddr *) &serveraddr, sizeof(serveraddr));
  sendto(socketfd, message, MAX, 0, (struct sockaddr*)NULL, sizeof(serveraddr));
  printf("Message sent.\n");

  //n = recvfrom(socketfd, (char *)buffer, MAX, MSG_WAITALL, (struct sockaddr *) &serveraddr, &length);
  //buffer[n] = '\0';
  recvfrom(socketfd, buffer, sizeof(buffer), 0, (struct sockaddr*)NULL, NULL);
  printf("Server: %s\n", buffer);

  close(socketfd);

  return 0;
}
