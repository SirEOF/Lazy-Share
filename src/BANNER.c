#include<stdio.h>
void banner()
{
   FILE* fptr;
   fptr = fopen("header.txt","r");

   char c = fgetc(fptr);
   while ( c!=EOF )
   {
       printf("%c",c);
       c = fgetc(fptr); 
   }

   fclose(fptr);

   return 0;
}