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
/* Maximum number of users that the system supports. */
#define SZ_USERS 50
/* Maximum number of tasks that the system supports. */
#define SZ_TASKS 10000
/* Maximum number of activities that the system supports. */
#define SZ_ACT 10

/* Maximum number of instructions that the system supports. */
#define MAX 50000

/* Number of required instructions by command 't'. */
#define INST_T 2
/* Number of required instructions by command 'm'. */
#define INST_N_D 1
/* Number of required instructions by command 'a'. */
#define INST_M 3

/* Command 'd'. */
#define D "d"
/* Command 'l'. */
#define L "l"

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

/* 'd' command error. */
#define D_ERROR "no such activity\n"
/* 'd' command output. */
#define D_OUT "%d %d %s\n"

/* 'a' command errors. */
#define A_ERROR1 "duplicate activity\n"
#define A_ERROR2 "invalid description\n"
#define A_ERROR3 "too many activities\n"
/* 'a' command output. */

/* Delimiters*/
#define NEWLINE "\n"
#define SPACE " "
#define SPACE_NEWLINE " \n"

#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define equal(A, B) (key(A) == key(B))

/* Structs and struct arrays*/
typedef struct
{
    char des_user[SZ_DES_UA];
} User;
/* Array of current system users. */
User system_users[SZ_USERS];

typedef struct
{
    char des_act[SZ_DES_UA];

} Activity;
/* Array of current system activities. */
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
/* Array of current system tasks. */
Task tasks[SZ_TASKS];
/* Auxiliary array used for listing tasks. */
Task aux_tasks[SZ_TASKS];

/* The number of users stored. */
int user_number = 0;
/* The number of tasks stored. */
int task_number = 0;
/* The number of activities stored. */
int act_number = 3;
/* System time. */
int time = 0;

/* Copies the global vector "tasks" to the global vector "aux_tasks", 
so as not to destroy or change the first one. */
void AuxTasks()
{
    int i;

    for (i = 0; i < task_number; i++)
    {
        strcpy(aux_tasks[i].des_task, tasks[i].des_task);
        strcpy(aux_tasks[i].task_act.des_act, tasks[i].task_act.des_act);
        strcpy(aux_tasks[i].task_user.des_user, tasks[i].task_user.des_user);
        aux_tasks[i].identifier = tasks[i].identifier;
        aux_tasks[i].starting_time = tasks[i].starting_time;
        aux_tasks[i].duration = tasks[i].duration;
    }
}

/* Auxiliary function for merge sorting, used to copy all the information from 
given task a to given task b. */
void MergeAux(int i, int j, Task a[SZ_TASKS], Task b[SZ_TASKS])
{
    strcpy(a[i].des_task, b[j].des_task);
    strcpy(a[i].task_act.des_act, b[j].task_act.des_act);
    strcpy(a[i].task_user.des_user, b[j].task_user.des_user);
    a[i].identifier = b[j].identifier;
    a[i].starting_time = b[j].starting_time;
    a[i].duration = b[j].duration;
}

/* Merges auxiliary array into aux_tasks, in order to sort tasks descriptions. */
void MergeStr(int l, int m, int r)
{
    int i, j, k;
    Task aux[SZ_TASKS];

    for (i = m + 1; i > l; i--)
        MergeAux(i - 1, i - 1, aux, aux_tasks);
    for (j = m; j < r; j++)
        MergeAux(r + m - j, j + 1, aux, aux_tasks);
    for (k = l; k <= r; k++)
    {
        if (strcmp(aux[j].des_task, aux[i].des_task) < 0)
            MergeAux(k, j--, aux_tasks, aux);
        else
            MergeAux(k, i++, aux_tasks, aux);
    }
}

/* Merges auxiliary array into aux_tasks, in order to sort tasks starting times. */
void MergeInt(int l, int m, int r)
{
    int i, j, k;
    Task aux[SZ_TASKS];

    for (i = m + 1; i > l; i--)
        MergeAux(i - 1, i - 1, aux, aux_tasks);
    for (j = m; j < r; j++)
        MergeAux(r + m - j, j + 1, aux, aux_tasks);
    for (k = l; k <= r; k++)
    {
        if (less(aux[j].starting_time, aux[i].starting_time))
            MergeAux(k, j--, aux_tasks, aux);
        else if (equal(aux[j].starting_time, aux[i].starting_time))
        {
            if (strcmp(aux[j].des_task, aux[i].des_task) < 0)
                MergeAux(k, j--, aux_tasks, aux);
            else
                MergeAux(k, i++, aux_tasks, aux);
        }
        else
            MergeAux(k, i++, aux_tasks, aux);
    }
}

/* Sorts tasks descriptions or starting times in aux_tasks, according to the given command. */
void MergeSort(char func[], int l, int r)
{
    int m = (r + l) / 2;
    if (r <= l) return;
    MergeSort(func, l, m);
    MergeSort(func, m + 1, r);
    if (strcmp(func, L) == 0) MergeStr(l, m, r);
    else if (strcmp(func, D) == 0) MergeInt(l, m, r);
}

/* Fills task t with the given information from the input and with the starting information as well. */
Task FillTask(char *v[MAX])
{
    Task t;

    t.duration = atoi(v[1]);
    strncpy(t.des_task, v[2], SZ_DES_T);
    strncpy(t.task_act.des_act, TO_DO, SZ_DES_UA);
    t.identifier = task_number + 1;
    t.starting_time = 0;

    return t;
}

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
    if (t.duration <= 0)
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

/* List tasks in the global vector "tasks" in alphabetical order. */
void ListsTasks_Alph(char *v[MAX])
{
    int i;

    AuxTasks();
    MergeSort(v[0], 0, task_number - 1);

    for (i = 0; i < task_number; i++)
    {
        printf(L_OUT, aux_tasks[i].identifier, aux_tasks[i].task_act.des_act, aux_tasks[i].duration, aux_tasks[i].des_task);
    }
}

/* Lists the tasks in the global vector "tasks" in order of input, given by given the string. */
void ListsTaks_Order(char *v[MAX])
{
    int i = 1;

    while (v[i] != NULL)
    {
        int val = atoi(v[i++]);
        if (val > tasks[task_number - 1].identifier || val < 0)
            printf(L_ERROR1, val);
        else
        {
            val--;
            printf(L_OUT, tasks[val].identifier, tasks[val].task_act.des_act, tasks[val].duration, tasks[val].des_task);
        }
    }
}

/* Advances in the system time by the given amount. */
void AdvanceTime(int n)
{
    if (!isdigit(n) && n < 0)
    {
        printf(N_ERROR1);
        return;
    }
    if (n == 0) printf(N_OUT, time);
    else
    {
        time += n;
        printf(N_OUT, time);
    }
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

/* Checks if a task is able to be moved to another activity or not, according to some errors. */
int MoveError(char *v[MAX])
{
    int j, user_exists = 0, act_exists = 0;

    if (atoi(v[1]) > task_number || atoi(v[1]) <= 0) 
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

/* Moves a task from one activity to another if moving doesn't raise any errors. */
void MoveTask(char *v[MAX])
{
    int id, duration, slack;

    if (MoveError(v) == 1) return;

    id = atoi(v[1]) - 1;

    strcpy(tasks[id].task_user.des_user, v[2]);

    if (strcmp(v[3], TO_DO) != 0 && strcmp(tasks[id].task_act.des_act, TO_DO) == 0)
    {
        strcpy(tasks[id].task_act.des_act, v[3]);
        tasks[id].starting_time = time;
    }

    strcpy(tasks[id].task_act.des_act, v[3]);
    
    if (strcmp(v[3], DONE) == 0)
    {
        if (strcmp(tasks[id].task_act.des_act, TO_DO) == 0) duration = 0;
        else duration = time - tasks[id].starting_time;
        slack = duration - tasks[id].duration;
        printf(M_OUT, duration, slack);
    }
}

/* Checks if the tasks from a given activity can be listed or not, according to some errors. */
int ListsTasksError(char *v[MAX])
{
    int i, act_exists = 0;

    for (i = 0; i < act_number; i++)
    {
        if (strcmp(activities[i].des_act, v[1]) == 0)
            act_exists = 1;
    }
    if (act_exists == 0)
    {
        printf(D_ERROR);
        return 1;
    }
    return 0;
}

/* Lists all the tasks in a given activity in ascending order of starting times, 
if listing these tasks doesn't raise any errors. */
void ListsTaks_Act(char *v[MAX])
{
    int i;

    if (ListsTasksError(v) == 1) return;

    AuxTasks();
    MergeSort(v[0], 0, task_number - 1);

    for (i = 0; i < task_number; i++)
    {
        if (strcmp(aux_tasks[i].task_act.des_act, v[1]) == 0)
            printf(D_OUT, aux_tasks[i].identifier, aux_tasks[i].starting_time, aux_tasks[i].des_task);
    }
}

/* Adds a new given activity to the global vector of activities, 
if adding doesn't raise any errors. */
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
    }
    for (i = 0; i < SZ_DES_UA; i++)
    {
        if (islower(a.des_act[i]))
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

/* Breaks the given string into tokens, considering that it's required that it receives
instructions. Used for these commands: 't', 'n', 'm', 'd'. */
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

/* Breaks the given string into tokens, considering that it may or may not receive
instructions. Used for these commands: 'l', 'u', 'a'. */
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

/* Makes the program run as commands are entered. */
int main()
{
    char str[MAX], *v[MAX];
    int i, n;
    User u;
    Task t;
    Activity a;

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
                t = FillTask(v);
                AddTask(t);
                task_number++;

                break;
            case 'l':
                BreakStr_Opt(str, SPACE, v);

                if (v[1] == NULL) ListsTasks_Alph(v);
                else ListsTaks_Order(v);

                break;
            case 'n':
                BreakStr_Requ(str, v, INST_N_D);

                n = atoi(v[1]);
                AdvanceTime(n);

                break;
            case 'u':
                BreakStr_Opt(str, SPACE_NEWLINE, v);

                if (v[1] == NULL)
                {
                    for (i = 0; i < user_number; i++)
                        printf(A_N_OUT, system_users[i].des_user);
                }
                else
                {
                    strncpy(u.des_user, v[1], SZ_DES_UA);
                    AddUser(u);
                    user_number++;
                }

                break;
            case 'm':
                BreakStr_Requ(str, v, INST_M);
                MoveTask(v);

                break;
            case 'd':
                BreakStr_Requ(str, v, INST_N_D);
                ListsTaks_Act(v);

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
                    strncpy(a.des_act, v[1], SZ_DES_UA);
                    AddActivity(a);
                    act_number++;
                }

                break;
        }
    }
}