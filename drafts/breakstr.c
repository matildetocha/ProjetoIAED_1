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
            token = strtok(NULL, "\n");
        n++;
    }

    while (token != NULL)
    {
        v[i++] = token;
        token = strtok(NULL, "\n");
    }
    v[i] = NULL;
}

void BreakStr_Opt(char str[MAX], const char delim[], char *v[MAX])
{
    char *token;
    int i = 0;

    token = strtok(str, " \n");

    while (token != NULL)
    {
        v[i++] = token;
        token = strtok(NULL, delim);
    }
    v[i] = NULL;
}

int main()
{
    char str[100] = "t 457290 heiow", *v[MAX];
    int i;
    BreakStr_Requ(str, v, 2);
    for (i = 0; i < 3; i++)
        puts(v[i]);
    return 0;
}
