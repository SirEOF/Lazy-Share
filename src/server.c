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
    int n,sockfd, newsockfd, clilen;
    int portno = 1234;
	char buffer[10000];
    struct sockaddr_in serv_addr, cli_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {error("ERROR opening socket") ;}
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) { error("ERROR on binding"); }
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) {error("ERROR on accept");}
        
	FILE *filepointer;
	int fileno=1;

	while(1)
	{
		int i = 0 ;
		bzero(buffer,10000);
		n = read(newsockfd,buffer,10000);
		if (n < 0){error("ERROR reading from socket");}
		if(strncmp(buffer,"complete",8)==0) {break;}	

		FILE *ptr;
		char ch[]="./LazyShare/Recieved/recX.txt";
		char temp[10000];
		ch[14] = '0' + fileno;
		ptr = fopen( ch , "wb" );
		fileno++;
		fputs(buffer,ptr);
		fclose(ptr);
		n=write(newsockfd,"Recieved",strlen("Recieved"));
		if( n < 0 ){error("ERROR writing to socket");}
		last_backup_write();
	}

	n=write(newsockfd,"Job Done",strlen("Job Done"));
}
