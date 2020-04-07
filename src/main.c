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

int main()
{
    create_workspace();
    banner();
    red();
    printf("The Last Backup was on :\n");
    last_backup_read();
    green();
    int choice = machine_page();
    
    if (choice == 1)
    {
        showip();
        int n;

        do    
        {
        n  = common_display_page();
            switch(n)
         {
            case 1:
                printf("\nWaiting for files....\n");
                server();
                break;
            case 2:
                last_backup_read();
                break;
            case 3:
                printf("\nGood Bye...!!!\n");
                exit(0);
                break;
            default:
                printf("\nDumbass can't even type correctly..!!!\n");
                exit(0);
         }
        }while(n != 0 && n != 3);

    }
    else if(choice == 2)
    {
        char *ip; 
        ip = input();
        int n = common_display_page();

        switch(n)
        {
            case 1:
                client(ip);
                break;

            case 2:
                last_backup_read();
                break;
            
            case 3:
                printf("\nGoodBye...!!!\n");
                exit(0);
            default:
                printf("\nDumbass can't even type correctly..!!!\n");
                exit(0);
        }
    }
    else if(choice == 3)
    {
        printf("\nGood Byee..!!!\n");
        exit(0);
    }
    else 
    {
        printf("\nCan't you even type correctly..!!!\n");
    }

    return 0;
}
