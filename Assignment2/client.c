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
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char userNameRequested[256];
    char portNumber[8];
    char serverName[9];
    // if (argc < 3) {
    //    fprintf(stderr,"usage %s hostname port\n", argv[0]);
    //    exit(0);
    // }
    // portno = atoi(argv[2]);
    printf("Please enter server name: ");
    bzero(serverName, 9);
    bzero(portNumber, 8);
    fgets(serverName, 11, stdin);
    printf("This is your server name: %s\n", serverName);
    
    printf("Please enter port number: ");

    fgets(portNumber, 7, stdin);

    portno = atoi(portNumber);
    printf("This is your port number: %s\n", portNumber);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    
    char sname[10];
    memcpy(sname, &serverName[0], 9);
    sname[9] = '\0';
    server = gethostbyname(sname);

    if(!server){
        printf("Not a valid server");
        exit(0);
    }
    printf("Name: %s\n", server->h_name);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");
    printf("Please enter the username: ");
    bzero(userNameRequested,256);
    fgets(userNameRequested,255,stdin);
    n = write(sockfd,userNameRequested,strlen(userNameRequested));
    if (n < 0)
         error("ERROR writing to socket");
    bzero(userNameRequested,256);
    n = read(sockfd,userNameRequested,255);
    if (n < 0)
         error("ERROR reading from socket");
    printf("%s\n",userNameRequested);
    close(sockfd);
    return 0;
}