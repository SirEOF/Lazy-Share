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

void client(char ip[])
{   
	
    char buffer[10000];
    int sockfd, portno = 1234, n;
    struct hostent *server;
    struct sockaddr_in serv_addr;
	server = gethostbyname(ip);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0) 
	{
		error("ERROR opening socket");
		exit(1);
	}

    if (server == NULL) 
	{
		fprintf(stderr,"ERROR, no such host\n");
		exit(1);
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
	int size , i = 0 ;
	struct dirent *de;
	DIR *dr = opendir("./LazyShare/Sent");
	
	while( ( de = readdir(dr) ) != NULL )
	{
		FILE *filepointer ;
		char ch[50]="./LazyShare/Sent";
		char *ch2=de->d_name;
	
		if((strcmp(".",ch2)==0)||(strcmp("..",ch2)==0))
			continue;

		strcat(ch,ch2);
		bzero(buffer,10000);
		filepointer = fopen(ch , "rb");
		fgets(buffer,10000,filepointer);
		
		printf("Sending File: %s\n",ch);
		
		n = write(sockfd,buffer,strlen(buffer));
		
		if (n < 0) {error("ERROR writing to socket");}
						
		bzero(buffer,10000);

		while(1)
		{
			bzero(buffer,10000);
			n = read( sockfd , buffer , 10000 );
			if( strncmp( "Recieved" , buffer , 5 ) == 0)
				break;
		}
		
		bzero(buffer,10000);
		printf("%d Sending File: \n",i+1);
		i++;
	}
	
	n = write(sockfd,"Complete",strlen("Complete"));
	if (n < 0) { error("ERROR writing to socket");}
	bzero(buffer,10000);
	last_backup_write();
    n = read(sockfd,buffer,10000);
    if (n < 0) { error("ERROR writing to socket");}
    printf("%s\n",buffer);
}

