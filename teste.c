#include <string.h>
#include <stdio.h>
#include <ctype.h>

int main()
{
    char str[80] = "";
    const char s[10] = "\0";
    char *token;

    fgets(str, 80, stdin);
    /* get the first token */
    token = strtok(str, s);
    if (token == NULL)
        printf("abc\n");

    /* walk through other tokens */
    while (token != NULL)
    {
        printf("ola\n");
        token = strtok(NULL, s);
    }

    return 0;
}