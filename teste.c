#include <string.h>
#include <stdio.h>

int main () {
   char str[80] = " pedrosilva";
   char *v[80];
   const char s[5] = " \n";
   v[0] = strtok(str, " \n");
   
   printf("%s\n", v[0]);

   return 0;
}

void adiciona_tarefa()
{
    Task t;
    t.identifier = 0;
    t.task_user.des_user = NULL;
    tasks[0] = t;
}

int BlankDesc(char str[])
{
    long unsigned int i = 0, blank_spaces = 0;
    for (i = 0; i < strlen(str); i++)
    {
        if (strcmp(str, " ") == 0)
            blank_spaces++;
    }
    if (blank_spaces == strlen(str))
        return 0;
    return 1;
}