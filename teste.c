#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main()
{
    char str[80] = "t 12 abc defg hij";
    const char s[10] = "";
    char *token;
    int val;

    /* get the first token */
    token = strtok(str, " ");

    /* walk through other tokens */
    while (token != NULL)
    {
        printf("ola\n");
        token = strtok(NULL, s);
    }

    return 0;
}