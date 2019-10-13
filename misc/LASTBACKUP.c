#include<unistd.h>
#include<stdlib.h>

void last_backup_write()
{
    system("date > lastbackup.txt");
}

void last_backup_read()
{
    system("cat lastbackup.txt");
}