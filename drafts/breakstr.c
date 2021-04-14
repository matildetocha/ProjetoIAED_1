#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 100
#define DONE "DONE"

void BreakStr_Requ(char str[MAX], char *v[MAX], int p)
{
    char *token;
    const char delim[MAX] = " ";
    int i = 0, n = 0;

    token = strtok(str, delim);

    while (n < p)
    {
        v[i++] = token;
        if (n < p - 1)
            token = strtok(NULL, delim);
        else
            token = strtok(NULL, "");
        n++;
    }

    while (token != NULL)
    {
        v[i++] = token;
        token = strtok(NULL, "");
    }
    v[i] = NULL;
}

int main()
{
    char str[80] = "m 1 maria DONE", *v[MAX];
    BreakStr_Requ(str, v, 3);
    if (strcmp(v[3], DONE) == 0)
        puts("iguais");
    return 0;
}
