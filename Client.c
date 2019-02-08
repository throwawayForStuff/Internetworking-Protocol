#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define IP_PROTOCOL 0
#define IP_ADDRESS "127.0.0.1"
#define PORT 15050
#define NET_BUFF_SIZE 32
#define cipherKey 'S'
#define sendrecvflag 0

//Clear buffer
void clearBuf(char * b)
{
  int i;
  for (i = 0; i < NET_BUFF_SIZE; i++)
    b[i] = '\0';
}

//For decryption. Needed?
char Cipher(char ch)
{
  return ch ^ cipherKey;
}

int recvFile(char * buf, int s)
{
  int i;
  char ch;

  for (i = 0; i < s; i++)
  {
    ch = buf[i];
    ch = Cipher(ch);
    if (ch == EOF)
      return 1;
    else
      printf("%c", ch);
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
  addr_con.sin_addr.s_addr = inet_addr(IP_ADDRESS);

  socketfd = socket(AF_INET, SOCK_DGRAM, IP_PROTOCOL);
  if (socketfd < 0)
    printf("\nCannot create socket.\n");
  else
    printf("\nSocket created.\n");

  while (1)
  {
    printf("\nEnter file name to receive: ");
    scanf("%s", net_buf);
    sendto(socketfd, net_buf, NET_BUFF_SIZE, sendrecvflag, (struct sockaddr*)&addr_con, addrlen);
    printf("\nFile received.\n");

    while (1)
    {
      clearBuf(net_buf);
      nBytes = recvfrom(socketfd, net_buf, NET_BUFF_SIZE, sendrecvflag, (struct sockaddr*)&addr_con, &addrlen);

      if (recvFile(net_buf, NET_BUFF_SIZE))
        break;
    }
  }
  return 0;

}
