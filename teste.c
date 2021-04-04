#include <string.h>
#include <stdio.h>

int main () {
   char str[80] = "sim snbscssjsjcsnbc uchiqancic";
   char *v[80];
   const char s[5] = " \n";
   v[0] = strtok(str, "\n");
   
   printf("%s\n", v[0]);

   return 0;
}