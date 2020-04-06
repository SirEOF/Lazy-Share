#include "client.h"
#include "server.h"
#include "utils.h"
#include "color.h"
#include <stdio.h>
#include <time.h>
#include <netdb.h> 
#include <dirent.h>
#include <stdlib.h>  
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

void server()
{   
    //system("./.hotspot.sh");
    int n,sockfd, newsockfd, clilen;
    int portno = 1234;
	long filelen = 256;
    char *buffer;
	buffer = (char *)malloc(filelen * sizeof(char));
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
        
	FILE *filepointer;
	int fileno=1;

	while(1)
	{
		int i=0;
		bzero(buffer,filelen);
		n = read(newsockfd,buffer,255);
		if (n < 0)
		{
			error("ERROR reading from socket");
		}

		if(strncmp(buffer,"complete",8)==0)
			break;	

		FILE *ptr;
		
		char ch[]="./Recieved/recX.txt";
		char temp[255];
			
		ch[14]='0' + fileno;
		ptr=fopen(ch,"wb");
		fileno++;
		fputs(buffer,ptr);
		fclose(ptr);
		n=write(newsockfd,"recieved",strlen("recieved"));
		if(n<0)
		{
			error("ERROR writing to socket");
		}
		
			last_backup_write();
			}

		n=write(newsockfd,"Job Done",strlen("Job Done"));
}
