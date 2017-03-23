/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
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
     int sockfd, newsockfd;
     socklen_t clilen;
     char userName[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     int portNumber;
     printf("Enter server port number: ");
     scanf("%d", &portNumber);

     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portNumber);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd,
                 (struct sockaddr *) &cli_addr,
                 &clilen);
         if (newsockfd < 0)
          error("ERROR on accept");
     bzero(userName,256);
     n = read(newsockfd,userName,255);
     if (n < 0) error("ERROR reading from socket");
     printf("Here is the user name: %s\n",userName);
     int isEqual = strncmp(userName, "jim", 3);
     printf("equal %i", isEqual);
     if(strncmp(userName, "jim", 3) == 0){
        printf("jim found");
     }
     n = write(newsockfd,"I got your message",18);
     if (n < 0) error("ERROR writing to socket");
     close(newsockfd);
     close(sockfd);
     return 0;
}