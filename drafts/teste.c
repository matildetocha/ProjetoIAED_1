#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main()
{
    char str[80], v[80] = "joao";
    const char s[10] = "\n";
    char *token;

    strcpy(str, v);
    puts(str);
    
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