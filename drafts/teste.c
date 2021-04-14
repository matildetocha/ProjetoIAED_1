#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main()
{
    char str[80] = "m 1 maria IN PROGRESS";
    const char s[10] = " ";
    char *token;

    /* get the first token */ 
    token = strtok(str, " ");

    /* walk through other tokens */
    while (token != NULL)
    {
        printf("%s\n", token);
        token = strtok(NULL, s); 
    } 
    return 0;
}