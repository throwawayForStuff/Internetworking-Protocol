#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define IP_PROTOCOL 0
#define PORT 15050
#define NET_BUFF_SIZE 32
#define cipherKey 'S'
#define sendrecvflag 0
#define nofile "File Not Found."

//Clear buffer
void clearBuf(char * b)
{
  int i;
  for (i = 0; i < NET_BUFF_SIZE; i++)
    b[i] = '\0';
}

//To encrypt. Needed?
char Cipher(char ch)
{
  return ch ^ cipherKey;
}

//Sending file
int sendFile(FILE* fp, char* buf, int s)
{
  int i;
  int length;
  char ch;
  char ch2;

  if (fp == NULL)
  {
    strcpy(buf, nofile);
    length = strlen(nofile);
    buf[length] = EOF;
    for (i = 0; i <= length; i++)
      buf[i] = Cipher(buf[i]);
    return 1;
  }

  for (i = 0; i < s; i++)
  {
    ch = fgetc(fp);
    ch2 = Cipher(ch);
    buf[i] = ch2;
    if (ch == EOF)
      return 1;
  }
  return 0;
}

int main()
{
  struct sockaddr_in addr_con;

  int socketfd;
  int nBytes;
  int addrlen = sizeof(addr_con);

  char net_buf[NET_BUFF_SIZE];
  FILE* fp;

  addr_con.sin_family = AF_INET;
  addr_con.sin_port = htons(PORT);
  addr_con.sin_addr.s_addr = INADDR_ANY;

  socketfd = socket(AF_INET, SOCK_DGRAM, IP_PROTOCOL);

  if (socketfd < 0)
    printf("\nCannot create socket.\n");
  else
    printf("\nSocket created.\n");

  if (bind(socketfd, (struct sockaddr*)&addr_con, sizeof(addr_con)) == 0)
    printf("\nBind successfully.\n");
  else
    printf("\nCannot bind.\n");

  while (1)
  {
    printf("\nWaiting for file name.\n");

    clearBuf(net_buf);

    nBytes = recvfrom(socketfd, net_buf, NET_BUFF_SIZE, sendrecvflag, (struct sockaddr*)&addr_con, &addrlen);

    fp = fopen(net_buf, "r");
    printf("\nFile Name: %s\n", net_buf);

    if (fp == NULL)
      printf("\nCannot open file.\n");
    else
      printf("\nFile opened.\n");

    while (1)
    {
      if (sendFile(fp, net_buf, NET_BUFF_SIZE))
      {
        sendto(socketfd, net_buf, NET_BUFF_SIZE, sendrecvflag, (struct sockaddr*)&addr_con, addrlen);
	break;
      }

      sendto(socketfd, net_buf, NET_BUFF_SIZE, sendrecvflag, (struct sockaddr*)&addr_con, addrlen);
      clearBuf(net_buf);
    }

    if (fp != NULL)
      fclose(fp);
  }
  return 0;
}
