/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

char* dataInput[5][50];

void error(const char *msg)
{
    perror(msg);
    exit(1);
}
int getNumberOfLines(){
    FILE *fp;
    int lines = 1;
    int ch = 0;
    fp = fopen("sample.txt", "r");
    while(!feof(fp)){
        ch = fgetc(fp);
        if(ch == '\n')
        {
            lines++;
        }
    }
    fclose(fp);
    return lines;
}
void printDataArray(){
    int lines = getNumberOfLines();
    for(int i=0; i < lines; i++){
        printf("[0][%i]: %s\n", i, dataInput[i][0]);
        printf("[1][%i]: %s\n", i, dataInput[i][1]);
    }
}

void readFile(){
    FILE *fp;
    int lines = getNumberOfLines();
    fp = fopen("sample.txt", "r");
    printf("Number of lines in file: %i\n", lines);
    
    for(int i=0; i < lines; i++){
        char* buff = (char *)malloc(255);
        char* buff2 = (char *)malloc(255);

        fscanf(fp, "%s", buff);
        dataInput[i][0] = buff;
        
        fscanf(fp, "%s", buff2);
        dataInput[i][1] = buff2;
    }
   
    fclose(fp);
  //  printDataArray();
}

int main(int argc, char *argv[])
{
    for(;;){
     int sockfd, newsockfd;
     socklen_t clilen;
     char userName[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     int portNumber;
     readFile();
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
     int isEqual = strcmp(userName, dataInput[2][0]);
     int lines = getNumberOfLines();
     char keyFound[255];
     if(strcmp(userName, "Terminate") == 10){
        close(newsockfd);
        close(sockfd);
        return 0;
     }
     else{
        //go through array and find equal matching username
       for(int i=0; i < lines; i++){
        if(strcmp(userName, dataInput[i][0]) == 10){
           // printf("[1][%i]: %s\n", i, dataInput[i][1]);
            strcpy(keyFound, dataInput[i][1]);
        }
        }
        if(strncmp(userName, "jim", 3) == 0){
        printf("jim found");
     }
     char output[200];
     snprintf(output, sizeof output, "The public key for user %s is %s", userName, keyFound);
     //printf("This is my output: %s", output);
     n = write(newsockfd,output, 400);
     if (n < 0) error("ERROR writing to socket");
     close(newsockfd);
     close(sockfd);
     //return 0;
    }
     }
}