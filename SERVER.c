#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include<stdlib.h>

void server()
{
    int n,sockfd, newsockfd, clilen;
    int portno = 1234;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        error("ERROR opening socket");
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        error("ERROR on binding");
    }

    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        
    if (newsockfd < 0)
    {
        error("ERROR on accept");
    }
        
    bzero(buffer,256);
    n = read(newsockfd,buffer,255);

    if (n < 0)
    {
        error("ERROR reading from socket");
    }

    FILE *filepointer;
    filepointer = fopen("recv.txt","w");
    last_backup_write();
    fputs(buffer,filepointer);
    printf("File Recieved\n");
    n = write(newsockfd,"Recieved",8);
    if (n < 0)
    {
        error("ERROR writing to socket");
    }

}

