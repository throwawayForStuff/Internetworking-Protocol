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
  int socketfd; //Our socket
  char buffer[MAX];
  char *hello = "Hello World";
  printf("\nHello World.\n");

  //To create socket, using socket system call
  //int s = (domain, type, protocol);
  

  return 0;
}

