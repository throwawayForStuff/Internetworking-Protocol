#include <stdio.h>
#include <sys.types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

void error(char * msg) {
    perror(msg);
}

int main(int argc, char * agrv[]) {

   //Return value for bind
   int bindVal;
   //Return value for listen
   int listenVal;
   //File descriptors
   int sockfd, newsockfd;
   //Port number variable
   int portno;
   //structure of server that will be used to store internet address of the server/client
   struct sockaddr_in serv_addr;
   struct sockaddr_in client_addr;

   //Stores the size of the address of the client. This needs to be accepted by the system call
   socklen_t clientLength;

   //Check for passed in args of port number
   if(agrc < 2) {
       printf("ERROR! No port provided!\n");
       exit(1);
   }
   sockfd = socket(SF_INET, SOCK_DGRAM, 0);

   if(sockfd == -1) {
       error("ERROR opening socket\n");
       exit(0);
   }

   portno = atoi(argv[1]);

   memset((char *) &serv_addr, 0, sizeof(serv_addr));


   //Fill the serv_addr structure for use in bind call

   serv_addr.sin_family = AF_INET;
   serv_addr.sin_port = htons(portno);
   serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

   //===========================
   //Binding starts here
   //Note: binding is a process that an application's socket tries
   //to bind to the port of a host

   bindVal = bind(sockfd, (struct sockaddr *)($serv_addr), sizeof(serv_addr));
   if(bindVal == -1){
       error("ERROR binding socket");
       exit(0);
   }


   listenVal = listen(sockfd, 5);
   if(listen == -1) {
       error("ERROR listening to upcoming to incoming connections.\n");
       exit(0);
   }

   clientLength = sizeof(client_addr);

   newsockfd = accept(sockfd, (struct sockaddr *) &client_addr, &clientLength);





}
