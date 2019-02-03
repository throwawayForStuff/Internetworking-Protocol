#include <iostream>
#include <cctype>
#include <cstring>
#include <sys/socket.h>

using namespace std;

int main()
{
  struct sockaddr_in serveraddr;
  struct sockaddr_in clientaddr;
  int socketfd; //Our socket
  cout << "Hello World" << endl;

  //To create socket, using socket system call
  //int s = (domain, type, protocol);
  

  return 0;
}

