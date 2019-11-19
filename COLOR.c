#include <stdio.h>
void red() 
{
  printf("\033[1;31m");
}

void yellow ()
{
  printf("\033[1;33m");
}

void green ()
{
  printf("\033[0;32m");
}

void reset () 
{
  printf("\033[0m");
}

void banner()
{
   FILE* fptr;
   fptr = fopen(".header.txt","r");
   char c = fgetc(fptr);
   while ( c!=EOF )
   {
     printf("%c",c);
     c = fgetc(fptr); 
   }
   fclose(fptr);
   return 0;
}
