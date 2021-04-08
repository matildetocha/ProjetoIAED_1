/*
 * File:  p1.c
 * Author:  Matilde Tocha 99108
 * Description: Projecto 1 - IAED 2020/21
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* Número máximo de caracteres para descrever um utilizador ou uma atividade. */
#define SZ_DES_UA 21
/* Número máximo de caracteres para descrever uma tarefa. */
#define SZ_DES_T 51
/* Número máximo de utilizadores que o sistema suporta. */
#define SZ_USERS 50
/* Número máximo de tarefas que o sistema suporta. */
#define SZ_TASKS 10000
/* Número máximo de atividades que o sistema suporta. */
#define SZ_ACT 10
/* qual é o número máximo de instruções que o sitema aceita?? */
#define MAX 100

/* Structs */
typedef struct
{
    char des_user[SZ_DES_UA];
} User;
User system_users[SZ_USERS];

typedef struct
{
    char des_act[SZ_DES_UA];

} Activity;
Activity activities[SZ_ACT];

typedef struct
{
    int identifier;
    char des_task[SZ_DES_T];
    int time;
    User task_user;
    Activity task_act;
    int starting_time;
} Task;
Task tasks[SZ_TASKS];

/* The number of users stored. */
int user_number = 0;
/* The number of tasks stored. */
int task_number = 0;

/* Adds a new given task to the global vector of tasks. */
void AddTask(Task t)
{
    int i = 0, cmp = 1;

    for (i = 0; i < SZ_TASKS; i++)
    {
        if (strcmp(t.des_task, tasks[i].des_task) == 0)
        {
            printf("duplicate description\n");
            return;
        }
    }
    if (strlen(tasks->des_task) == SZ_TASKS)
    {
        printf("too many tasks\n");
        return;
    }
    else strcpy(tasks[1].des_task, t.des_task);
}

/* Adds a new given user to the global vector of system_users. */
void AddUser(User v)
{
    int i = 0;

    for (i = 0; i < SZ_USERS; i++)
    {
        if (strcmp(v.des_user, system_users[i].des_user) == 0)
        {
            printf("user already exists\n");
            user_number--;
            return;
        }
    }
    if (strlen(system_users->des_user) == SZ_USERS)
    {
        printf("too many users\n");
        user_number--;
        return;
    }
    else strcpy(system_users[user_number].des_user, v.des_user);
}

void BreakStr(char str[], const char delim[], char *v[])
{
    char *token;
    int i = 0;

    /* Gets the first token. */
    token = strtok(str, " \n");

    /* Walks through other tokens. */
    while (token != NULL)
    {
        v[i++] = token;
        token = strtok(NULL, delim);
    }
    v[i] = NULL;
}

int main()
{
    char str[MAX], *v[MAX];
    int i = 0;
    User u;

    strcpy(activities[0].des_act, "TO DO");
    strcpy(activities[1].des_act, "IN PROGRESS");
    strcpy(activities[2].des_act, "DONE");

    for (;;)
    {
        fgets(str, MAX, stdin);
        switch (str[0])
        {
            case 't':
                break;
            case 'l':
                break;
            case 'n':
                break;
            case 'u':
                BreakStr(str, "\n", v);
                if (v[1] == NULL)
                {
                    for (i = 0; i < user_number; i++)
                        printf("%s\n", system_users[i].des_user);
                }
                else
                {
                     strcpy(u.des_user, v[1]);
                    AddUser(u);
                    user_number++;                   
                }
                break;
            case 'm':
                break;
            case 'd':
                break;
            case 'a':
                break;
            case 'q':
                exit(EXIT_SUCCESS);
        }
    }
}