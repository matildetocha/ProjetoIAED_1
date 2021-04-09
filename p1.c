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
/* Número máximo de instruções que o sitema suporta*/
#define MX 6002

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
/* Time */
int time = 0;

/* Adds a new given task to the global vector of tasks. */
void AddTask(Task t)
{
    int i = 0;

    for (i = 0; i < SZ_TASKS; i++)
    {
        if (strcmp(t.des_task, tasks[i].des_task) == 0)
        {
            printf("duplicate description\n");
            task_number--;
            return;
        }
    }
    if (task_number == SZ_TASKS)
    {
        printf("too many tasks\n");
        task_number--;
        return;
    }
    else if (!isdigit(t.time) && t.time < 0)
    {
        printf("invalid duration\n");
        task_number--;
        return;
    }

    else
    {
        strcpy(tasks[task_number].des_task, t.des_task);
        strcpy(tasks[task_number].task_act.des_act, t.task_act.des_act);
        tasks[task_number].identifier = t.identifier;
        tasks[task_number].time = t.time;
        tasks[task_number].starting_time = t.starting_time;

        printf("task %d\n", task_number + 1);
    }
}

/* Lists the tasks in the global vector tasks in order of input, given by given the string. */
void ListsTaks_Order(char *v[MAX])
{
    int i = 1, val;
    while (v[i] != NULL)
    {
        val = atoi(v[i]);
        if (val > task_number)
        {
            printf("%d: no such task\n", val);
            return;
        }
        val--;
        printf("%d %s #%d %s", tasks[val].identifier, tasks[val].task_act.des_act, tasks[val].time, tasks[val].des_task);
        i++;
    }
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
    if (user_number == SZ_USERS)
    {
        printf("too many users\n");
        user_number--;
        return;
    }
    else
        strcpy(system_users[user_number].des_user, v.des_user);
}

void BreakTask(char str[MAX], const char delim[], char *v[MAX])
{
    char *token;
    int i = 0;

    token = strtok(str, delim);
    v[i++] = token;

    token = strtok(NULL, delim);
    v[i++] = token;

    token = strtok(NULL, "");
    v[i++] = token;
    v[i] = NULL;
}

/* Breaks the given string into tokens, considering that it may or may not receive instructions. Used for these commands: 'l', 'u', 'a'. */
void BreakStr_Opt(char str[MAX], const char delim[], char *v[MAX])
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
    Task t;

    strcpy(activities[0].des_act, "TO DO");
    strcpy(activities[1].des_act, "IN PROGRESS");
    strcpy(activities[2].des_act, "DONE");

    for (;;)
    {
        fgets(str, MAX, stdin);

        i = 0;
        switch (str[0])
        {
            case 't':
                BreakTask(str, " ", v);

                i++;

                t.time = atoi(v[i++]);
                strcpy(t.des_task, v[i]);
                strcpy(t.task_act.des_act, "TO DO");
                t.identifier = task_number + 1;
                t.starting_time = 0;

                AddTask(t);
                task_number++;

                break;
            case 'l':
                BreakStr_Opt(str, " ", v);

                if (v[1] == NULL)
                {
                    for (i = 0; i < task_number; i++)
                        printf("%d %s #%d %s", tasks[i].identifier, tasks[i].task_act.des_act, tasks[i].time, tasks[i].des_task);
                }
                else
                    ListsTaks_Order(v);

                break;
            case 'n':
                BreakStr_Opt(str, "\n", v);

                break;
            case 'u':
                BreakStr_Opt(str, "\n", v);

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