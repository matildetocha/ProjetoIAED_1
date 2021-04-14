/*
 * File:  p1.c
 * Author:  Matilde Tocha 99108
 * Description:  Projecto 1 - IAED 2020/21
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* Maximum number of characters used to describe an user or an activity.*/
#define SZ_DES_UA 21
/* Maximum number of characters used to describe a task. */
#define SZ_DES_T 51
/* Maximum number of users that the system supports.. */
#define SZ_USERS 50
/* Maximum number of tasks that the system supports. */
#define SZ_TASKS 10000
/* Maximum number of activities that the system supports. */
#define SZ_ACT 10

/* Maximum number of instructions that the system supports. */
#define MAX 6002

/* Number of required instructions by command 't'. */
#define INST_T 2
/* Number of required instructions by command 'm'. */
#define INST_N 1
/* Number of required instructions by command 'a'. */
#define INST_M 3

/* Activity TO DO. */
#define TO_DO "TO DO"
/* Activity IN PROGRESS*/
#define IN_PROGRESS "IN PROGRESS"
/* Activity DONE. */
#define DONE "DONE"

/* 't' command errors. */
#define T_ERROR1 "too many tasks\n"
#define T_ERROR2 "duplicate description\n"
#define T_ERROR3 "invalid duration\n"
/* 't' command output. */
#define T_OUT "task %d\n"

/* 'l' command errors. */
#define L_ERROR1 "%d: no such task\n"
/* 'l' command output.*/
#define L_OUT "%d %s #%d %s\n"

/* 'n' command errors. */
#define N_ERROR1 "invalid time\n"
/* 'n' command output. */
#define N_OUT "%d\n"

/* 'u' command errors. */
#define U_ERROR1 "user already exists\n" 
#define U_ERROR2 "too many users\n"
/* 'u' and 'a' commands outputs. */
#define A_N_OUT "%s\n"

/* 'm' command errors. */
#define M_ERROR1 "no such task\n"
#define M_ERROR2 "task already started\n"
#define M_ERROR3 "no such user\n"
#define M_ERROR4 "no such activity\n"
/* 'm' command output. */
#define M_OUT "duration=%d slack=%d\n"

/* 'a' command errors. */
#define A_ERROR1 "duplicate activity\n"
#define A_ERROR2 "invalid description\n"
#define A_ERROR3 "too many activities\n"
/* 'a' command output. */

/* Delimiters*/
#define NEWLINE "\n"
#define SPACE " "
#define SPACE_NEWLINE " \n"

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
    int duration;
    User task_user;
    Activity task_act;
    int starting_time;
} Task;
Task tasks[SZ_TASKS];

/* The number of users stored. */
int user_number = 0;
/* The number of tasks stored. */
int task_number = 0;
/* The number of activities stored. */
int act_number = 3;
/* System time. */
int time = 0;

/* Checks if a task can be added to the global vector "tasks", according to some errors. */
int AddTaskError(Task t)
{
    int i;

    if (task_number == SZ_TASKS)
    {
        printf(T_ERROR1);
        task_number--;
        return 1;
    }
    for (i = 0; i < task_number; i++)
    {
        if (strcmp(t.des_task, tasks[i].des_task) == 0)
        {
            printf(T_ERROR2);
            task_number--;
            return 1;
        }
    }
    if (!isdigit(t.duration) && t.duration < 0)
    {
        printf(T_ERROR3);
        task_number--;
        return 1;
    }
    return 0;
}

/* Adds a new given task by filling the global vector "tasks" with the information 
from the new task, if that task doesn't raise any errors. */
void AddTask(Task t)
{
    if (AddTaskError(t) == 1) return;
    else
    {
        strcpy(tasks[task_number].des_task, t.des_task);
        strcpy(tasks[task_number].task_act.des_act, t.task_act.des_act);
        tasks[task_number].identifier = t.identifier;
        tasks[task_number].duration = t.duration;
        tasks[task_number].starting_time = t.starting_time;

        printf(T_OUT, task_number + 1);
    }
}

/* Lists the tasks in the global vector "tasks" in order of input, given by given the string. */
void ListsTaks_Order(char *v[MAX])
{
    int i = 1;
    while (v[i] != NULL)
    {
        int val = atoi(v[i++]);
        if (val > tasks[task_number - 1].identifier)
        {
            printf(L_ERROR1, val);
            return;
        }
        val--;
        printf(L_OUT, tasks[val].identifier, tasks[val].task_act.des_act, tasks[val].duration, tasks[val].des_task);
    }
}

/* Advances in the system time by the given amount. */
void AdvanceTime(int n)
{
    if (!isdigit(n) && n <= 0)
        printf(N_ERROR1);
    else time += n;
}

/* Adds a new given user to the global vector of system users, 
if that user doesn't raise any errors. */
void AddUser(User v)
{
    int i;

    for (i = 0; i < user_number; i++)
    {
        if (strcmp(v.des_user, system_users[i].des_user) == 0)
        {
            printf(U_ERROR1);
            user_number--;
            return;
        }
    }
    if (user_number == SZ_USERS)
    {
        printf(U_ERROR2);
        user_number--;
        return;
    }
    else
        strcpy(system_users[user_number].des_user, v.des_user);
}

/* Checks if a task is able to move to another activity or not, according to some errors */
int MoveError(char *v[MAX])
{
    int j, user_exists = 0, act_exists = 0; 
    
    if (atoi(v[1]) > task_number || atoi(v[1]) < 0)      /* // ? NAO FUNCIONA COM ISDIGIT, PORQUE? */
    {
        printf(M_ERROR1);
        return 1;
    }
    for (j = 0; j < task_number; j++)
    {
        if (strcmp(tasks[j].task_act.des_act, TO_DO) && strcmp(v[3], TO_DO) == 0)
        {
            printf(M_ERROR2);
            return 1;
        }
    }
    for (j = 0; j < user_number; j++)
    {
        if (strcmp(v[2], system_users[j].des_user) == 0)
            user_exists = 1;
    }
    if (user_exists == 0)
    {
        printf(M_ERROR3);
        return 1;
    }
    for (j = 0; j < act_number; j++)
    {
        if (strcmp(v[3], activities[j].des_act) == 0)
            act_exists = 1;
    }
    if (act_exists == 0)
    {
        printf(M_ERROR4);
        return 1;
    } 
    return 0;
} 

/* Moves a task from one activity to another. */ 
void MoveTask(char *v[MAX])
{
    int id, duration, slack;

    if (MoveError(v) == 1) return;
    
    id = atoi(v[1]) - 1; 

    strcpy(tasks[id].task_user.des_user, v[2]);
    strcpy(tasks[id].task_act.des_act, v[3]);
    
    if (!strcmp(v[3], TO_DO) && strcmp(tasks[id].task_act.des_act, TO_DO) == 0)
        tasks[id].starting_time = time;
    else if (strcmp(v[3], DONE) == 0)
    {   
        if (strcmp(tasks[id].task_act.des_act, TO_DO)) duration = 0;
        else duration = time - tasks[id].starting_time;
        slack = duration -  tasks[id].duration;
        printf(M_OUT, duration, slack); 
    }
}

/* Adds a new given activity to the global vector of activities. */
void AddActivity(Activity a)
{
    int i;

    for (i = 0; i < act_number; i++)
    {
        if (strcmp(a.des_act, activities[i].des_act) == 0)
        {
            printf(A_ERROR1);
            act_number--;
            return;
        }
        else if (islower(a.des_act[i]))
        {    
            printf(A_ERROR2);
            act_number--;
            return;
        }
    }
    if (act_number == SZ_ACT)
    {
        printf(A_ERROR3);
        act_number--;
        return;
    }
    else
        strcpy(activities[act_number].des_act, a.des_act);
}

/* Breaks the given string into tokens, considering that it's required that it receives instructions. Used for these commands: 't', 'n', 'm', 'd'. */
void BreakStr_Requ(char str[MAX], char *v[MAX], int p)
{
    char *token;
    int i = 0, n = 0;

    token = strtok(str, SPACE);

    while (n < p)
    {
        v[i++] = token;
        if (n < p - 1)
            token = strtok(NULL, SPACE);
        else
            token = strtok(NULL, NEWLINE);
        n++;
    }

    while (token != NULL)
    {
        v[i++] = token;
        token = strtok(NULL, NEWLINE);
    }
    v[i] = NULL;
}

/* Breaks the given string into tokens, considering that it may or may not receive instructions. Used for these commands: 'l', 'u', 'a'. */
void BreakStr_Opt(char str[MAX], const char delim[], char *v[MAX])
{
    char *token;
    int i = 0;

    token = strtok(str, SPACE_NEWLINE);

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
    int i, n;
    User u;
    Task t;
    Activity a;

    /* Creates 3 activites. */
    strcpy(activities[0].des_act, TO_DO);
    strcpy(activities[1].des_act, IN_PROGRESS);
    strcpy(activities[2].des_act, DONE);

    for (;;)
    {
        fgets(str, MAX, stdin);

        i = 0;
        memset(v, 0, MAX - 1);
        switch (str[0])
        {
            case 'q':
                exit(EXIT_SUCCESS);
                break;
            case 't':
                BreakStr_Requ(str, v, INST_T);

                i++;
                /* Fills task t with the given information from the input and with the starting information as well. */
                t.duration = atoi(v[i++]);
                strcpy(t.des_task, v[i]);
                strcpy(t.task_act.des_act, TO_DO);
                t.identifier = task_number + 1;
                t.starting_time = 0;

                AddTask(t);
                task_number++;

                break;
            case 'l':
                BreakStr_Opt(str, SPACE, v);

                if (v[1] == NULL)
                {
                    for (i = 0; i < task_number; i++)
                        printf(L_OUT, tasks[i].identifier, tasks[i].task_act.des_act, tasks[i].duration, tasks[i].des_task);
                }
                else
                    ListsTaks_Order(v);

                break;
            case 'n':
                BreakStr_Requ(str, v, INST_N);

                n = atoi(v[1]);
                if (n == 0) printf(N_OUT, time);
                else
                {
                    AdvanceTime(n);
                    printf(N_OUT, time);
                }

                break;
            case 'u':
                BreakStr_Opt(str, NEWLINE, v);

                if (v[1] == NULL)
                {
                    for (i = 0; i < user_number; i++)
                        printf(A_N_OUT, system_users[i].des_user);
                }
                else
                {
                    strcpy(u.des_user, v[1]);
                    AddUser(u);
                    user_number++;
                }

                break;
            case 'm':
                BreakStr_Requ(str, v, INST_M);
                MoveTask(v);

                break;
            case 'd':
                break;
            case 'a':
                BreakStr_Opt(str, NEWLINE, v);

                if (v[1] == NULL)
                {
                    for (i = 0; i < act_number; i++)
                        printf(A_N_OUT, activities[i].des_act);
                }
                else
                {
                    strcpy(a.des_act, v[1]);
                    AddActivity(a);
                    act_number++;
                }

                break;
            }
    }
}