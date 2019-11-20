#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include<string.h>
#include<dirent.h>

void client(char ip[])
{
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

    //SHUBHAM ARYA
    // FILE *filepointer;
    // filepointer = fopen("test.txt" , "r");
    // fgets(buffer,255,filepointer);
    
    // n = write(sockfd,buffer,strlen(buffer));
    
    // if (n < 0) 
    //      {
    //         error("ERROR writing to socket");
    //      }
    
    // bzero(buffer,256);
    // last_backup_write();
    // n = read(sockfd,buffer,255);
    
    // if (n < 0) 
    //      {
    //          error("ERROR reading from socket");
    //      }

    // printf("%s\n",buffer);


    // DIXIT

    int i=0;
	struct dirent *de;
	DIR *dr = opendir("./files");
	while((de=readdir(dr))!=NULL)
	{
		if(i>=0)
		{
			FILE *filepointer;
			char ch[50]="./files/";
			char *ch2=de->d_name;
			if((strcmp(".",ch2)==0)||(strcmp("..","ch2")==0))
				continue;
			strcat(ch,ch2);
			bzero(buffer,256);
			printf("file sending is %s\n",ch);
			filepointer = fopen(ch , "r");
    			fgets(buffer,255,filepointer);
    			n = write(sockfd,buffer,strlen(buffer));
			if (n < 0) 
        		{
            			error("ERROR writing to socket");
         		}
    			  			
			bzero(buffer,256);
    			printf("%d file send\n",i+1);
    				
		
		}
		/*while(1)
		{
			n = read(sockfd,buffer,256);
			if(strcmp(buffer,"done")==0)
				break;
		}*/
		i++;
	}
	/*buffer="complete";*/
	n=write(sockfd,"complete",strlen("complete"));
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
