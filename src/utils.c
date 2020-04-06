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
#include <sys/stat.h>
#include <netinet/in.h>
#include <string.h>

char ip[50];
void linHotspot()
{
    char *c;
    printf("Do you want to connect with other device using hotspot ?\n");
    printf("Choose 'n' if you are already connected(y/n)\n> ");
    fgets(c,3,stdin);

    if(*c == 'y')
    {
        printf("Were you previously connected to the other device using LazyShare ?(y/n)\n> ");
        fgets(c,3,stdin);

        if(*c == 'y')
       {
        printf("\nCreating Hotspot...!!\n");
        system("nmcli con add type wifi ifname wlan0 con-name Hostspot autoconnect yes ssid LazyShare");
        system("nmcli con modify Hostspot 802-11-wireless.mode ap 802-11-wireless.band bg ipv4.method shared");
        system("nmcli con modify Hostspot wifi-sec.key-mgmt wpa-psk");
        system("nmcli con modify Hostspot wifi-sec.psk 'asdfrewq'");
        system("nmcli con up Hostspot");
       }

       else if(*c == 'n')
       {
         printf("\nTurning Hotspot on\n");
         system("nmcli con down Hostspot");
       }   

    }
    return;
}

void linWifi()
{
    char *c;
    printf("Do you want to connect to the other device using wifi?(y/n)\n> ");
    fgets(c,3,stdin);
    if(*c == 'y')
    {
        printf("\nConnecting...!!\n");
        system("nmcli dev wifi connect LazyShare password asdfrewq ");
    }
}

void error(char *msg)
{
    red();
    perror(msg);
    exit(1);
}

char *input()
{
    printf("Enter the IP you got from server side: ");
    scanf("%s",ip);
    return ip;
}

void last_backup_write()
{
    time_t now;
    FILE *fptr;
    fptr = fopen("./LazyShare/.conf/lastbackup.txt","w");
    int hours, minutes, seconds, day, month, year;
    char str[1000];
    struct tm *local = localtime(&now);
    
    day = local->tm_mday;
    month = local->tm_mon + 1;
    year = local->tm_year + 1900;
    hours = local->tm_hour;
    minutes = local->tm_min;
    seconds = local->tm_sec;
    
    sprintf(str ,"Last Backup time is : %02d:%02d:%02d am\n", hours, minutes, seconds);
    fprintf(fptr,"%s",str);
    sprintf(str,"Date is : %02d/%02d/%d\n", day, month, year);
    fprintf(fptr,"%s",str);
    fclose(fptr);
}

void last_backup_read()
{
    FILE *fptr;
    fptr = fopen("./LazyShare/.conf/lastbackup.txt" , "r");
    char c = fgetc(fptr); 
    while (c != EOF) 
    { 
        printf ("%c", c); 
        c = fgetc(fptr); 
    }
    fclose(fptr); 
}

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

int machine_page()
{
    int a;
    yellow();
    printf("\n1. Recieve Files\n2. Send Files\n3. Exit\n> ");
    scanf("%d",&a);
    return a;
}

int showip()
{
    red();
    printf("\nThe server IP :- \n");
    yellow();
    system("echo \"[ $(hostname -I)]\"" );
    red();
    return 0;
}

void banner()
{
    green();
    printf("==========================================================\n");
    yellow();
    printf(" _                      ____  _                     \n");
    printf("| |    __ _ _____   _  / ___|| |__   __ _ _ __ ___    \n");
    printf("| |   / _` |_  / | | | \\___ \\| '_ \\ / _` | '__/ _ \\\n");
    printf("| |__| (_| |/ /| |_| |  ___) | | | | (_| | | |  __/   \n");
    printf("|_____\\__,_/___|\\__, | |____/|_| |_|\\__,_|_|  \\___|\n");
    printf("                 |___/                                 \n");
    green();
    printf("==========================================================\n");
    reset();
}

void create_workspace()
{
    mkdir("LazyShare", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    mkdir("LazyShare/Sent", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    mkdir("LazyShare/Recieved", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    mkdir("LazyShare/.conf", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    FILE *fptr;
    fptr = fopen("./LazyShare/.conf/lastbackup.txt","w");
    fprintf(fptr,"No Backup yet");
    fclose(fptr);    
}

