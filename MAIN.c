
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdlib.h>  

char ip[50];
void server();
void client(char ip[]);

void wificonnect()
{
    system("./wifi");
}

// Shows Error 
void error(char *msg)
{
    red();
    perror(msg);
    exit(1);
}

// Inputs IP to Send it to Client
void input()
{
    printf("Enter the IP you got from server side: ");
    scanf("%s",&ip);
}

// Writes Last Backup Time to a File
void last_backup_write()
{
    system("date > .lastbackup.txt");
}

// Reads Last Backup Time from a File
void last_backup_read()
{
    system("cat .lastbackup.txt");
}

// Choices For the User
int common_display_page()
{
    int choice;
    green();
    printf("\nChoose from the following:");
    printf("\n1. Start ");
    printf("\n2. View Last Backup");
    printf("\n3. Exit\n> ");
    scanf("%d",&choice);
    return choice;
}

// Choose if the Machine is Server/Client
int machine_page()
{
    int a;
    yellow();
    printf("\nType 1 if this is the server machine\nType 2 if this is a client machine\n> ");
    scanf("%d",&a);
    return a;
}

// Shows the IP of the Machine
int showip()
{
    red();
    printf("\nThis is the server IP details ==>\n");
    yellow();
    printf("============================================================\n\n");
    system("ifconfig wlan0 | tr ' ' '\n' | grep -A1 inet");
    printf("\n==========================================================\n");
    red();
    printf("\nUse the value of inet as IP address on the client side\n");
    return 0;
}

// Main Function
int main()
{
    yellow();
    banner();
    green();
    wificonnect();

    int choice = machine_page();

    /* Runs the server */

    if (choice == 1)
        {
            showip();    // Shows the ip of the server
            int n = common_display_page(); // Calls the display page
                
            switch(n)
            {
                case 1:

                    server();
                    break;
                
                case 2:
                    last_backup_read();
                    break;
                
                default:
                    exit(0);
            }

        }


    /* Runs the client */

    else if(choice == 2)
        {
            input();
            int n = common_display_page();

            switch(n)
            {
                case 1:
                    client(ip);
                    break;

                case 2:
                    last_backup_read();
                    break;
                
                default:
                    exit(0);
            }
        }
        return 0;
}
