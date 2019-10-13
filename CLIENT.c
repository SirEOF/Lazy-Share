// Main client program
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include<string.h>
#include "color.h"
#include "cs.h"

void last_backup_write();

#define FILE_TO_SEND test.txt

void client(char ip[])
{
    /* Declarations*/
    int sockfd, portno = 1234, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];

    
    server = gethostbyname(ip);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0) 
        {
            error("ERROR opening socket");
        }
    

    if (server == NULL) 
        {
            fprintf(stderr,"ERROR, no such host\n");
            exit(0);
        }

    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    
    
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        {
            error("ERROR connecting");
        }

    printf("Sending File: ");
    bzero(buffer,256);
    FILE *filepointer;
    filepointer = fopen("test.txt" , "r");
    fgets(buffer,255,filepointer);
    
    n = write(sockfd,buffer,strlen(buffer));
    
    if (n < 0) 
         {
            error("ERROR writing to socket");
         }
    
    bzero(buffer,256);
    last_backup_write();
    n = read(sockfd,buffer,255);
    
    if (n < 0) 
         {
             error("ERROR reading from socket");
         }

    printf("%s\n",buffer);
}

