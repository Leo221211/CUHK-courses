#include <stdio.h>

int main()
{
   char str[100];

   scanf("%99s", str);

   fprintf(stdout,"Welcome to MOCK!\n%s\n", str);
   fprintf(stderr, "This is the stderr\n");

   return 0;
}
