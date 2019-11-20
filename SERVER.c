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

    // n = read(newsockfd,buffer,255);

    // if (n < 0)
    // {
    //     error("ERROR reading from socket");
    // }
    // FILE *filepointer;
    // filepointer = fopen("recv.txt","w");
    // last_backup_write();
    // fputs(buffer,filepointer);
    // printf("File Recieved\n");
    // n = write(newsockfd,"Recieved",8);
    // if (n < 0)
    // {
    //     error("ERROR writing to socket");
    // }


    //char ch[]="./recieved/recX.txt";
	//int i=1;
	FILE *filepointer;
	while(1)
	{
        bzero(buffer,256);
        n = read(newsockfd,buffer,255);
        if (n < 0)
        {
            error("ERROR reading from socket");
        }

    	printf("buffer is %s\n",buffer);
	//printf("compare result for %s is %d",buffer,strncmp("complete",buffer,8));
        /*if(strncmp("complete",buffer,8)==0)
        {
            //fclose(filepointer);
            n = write(newsockfd,"Recieved",8);
        
                if (n < 0) error("ERROR writing to socket");
            break;
        }
        else
        {
            if(1)//if(i==1)
            {
                ch[14]=i+ '0';
                filepointer = fopen(ch,"w");
            }
                
                
            fputs(buffer,filepointer);
            fclose(filepointer);
            printf("%d File Recieved\n",i);
            i++;
            //ch[14]=i+'0';	
            //filepointer=fopen(ch,"w");
            //n = write(newsockfd,"done",5);
                
        }*/


	//================================================================================
	//ARYA DONT ASK ME

	int i=0;

	FILE *ptr;
	int fileno=1,i_temp=0;
	char ch[]="./recieved/recX.txt";
	char temp[255];
		
	ch[14]='0' + fileno;
	//printf("success\n");
	
	ptr=fopen(ch,"w");
	
	while(buffer[i]!='\0')
	{
		
		if(buffer[i]=='\n')
		{
			fputs(temp,ptr);
			bzero(temp,255);
			fclose(ptr);
			fileno++;
			i_temp=0;
			ch[14]=fileno+'0';
			ptr=fopen(ch,"w");
		}
		else
		{
			temp[i_temp]=buffer[i];
			i_temp++;
		}
		i++;
	

	}



	//=================================================================================
        last_backup_write();
        break;
        }
	//fclose(ptr);
	
}

