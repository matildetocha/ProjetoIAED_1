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

/* Adds a new given task to the global vector of tasks. */
void AddTask(Task t)
{
    int i;

    if (task_number == SZ_TASKS)
    {
        printf("too many tasks\n");
        task_number--;
        return;
    }
    for (i = 0; i < task_number; i++)
    {
        if (strcmp(t.des_task, tasks[i].des_task) == 0)
        {
            printf("duplicate description\n");
            task_number--;
            return;
        }
    }

    if (!isdigit(t.duration) && t.duration < 0)
    {
        printf("invalid duration\n");
        task_number--;
        return;
    }

    else
    {
        /* Adds a new task by filling the global vector "tasks" with the information from the new task. */
        strcpy(tasks[task_number].des_task, t.des_task);
        strcpy(tasks[task_number].task_act.des_act, t.task_act.des_act);
        tasks[task_number].identifier = t.identifier;
        tasks[task_number].duration = t.duration;
        tasks[task_number].starting_time = t.starting_time;

        printf("task %d\n", task_number + 1);
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
            printf("%d: no such task\n", val);
            return;
        }
        val--;
        printf("%d %s #%d %s\n", tasks[val].identifier, tasks[val].task_act.des_act, tasks[val].duration, tasks[val].des_task);
    }
}

/* Advances in the system time by the given amount. */
void AdvanceTime(int n)
{
    if (!isdigit(n) && n <= 0)
        printf("invalid time\n");
    else time += n;
}

/* Adds a new given user to the global vector of system users. */
void AddUser(User v)
{
    int i;

    for (i = 0; i < user_number; i++)
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

/* Checks if a task is able to move or not, according to some errors */
int MoveError(char *v[MAX])
{
    int j, user_exists = 0, act_exists = 0; 
    
    if (atoi(v[1]) > task_number || atoi(v[1]) < 0)      /* // ? NAO FUNCIONA COM ISDIGIT, PORQUE? */
    {
        printf("no such task\n");
        return 1;
    }
    for (j = 0; j < task_number; j++)
    {
        if (strcmp(tasks[j].task_act.des_act, TO_DO) && strcmp(v[3], TO_DO) == 0)
        {
            printf("task already started\n");
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
        printf("no such user\n");
        return 1;
    }
    for (j = 0; j < act_number; j++)
    {
        if (strcmp(v[3], activities[j].des_act) == 0)
            act_exists = 1;
    }
    if (act_exists == 0)
    {
        printf("no such activity\n");
        return 1;
    } 
    return 0;
} 

/* Moves a task from one activity to another. */ 
void MoveTask(char *v[MAX])
{
    int id, duration, slack;

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
        printf("duration=%d slack=%d\n", duration, slack); 
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
            printf("duplicate activity\n");
            act_number--;
            return;
        }
        else if (islower(a.des_act[i]))
        {    
            printf("invalid description\n");
            act_number--;
            return;
        }
    }
    if (act_number == SZ_ACT)
    {
        printf("too many activities\n");
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

/* Breaks the given string into tokens, considering that it may or may not receive instructions. Used for these commands: 'l', 'u', 'a'. */
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
                        printf("%d %s #%d %s\n", tasks[i].identifier, tasks[i].task_act.des_act, tasks[i].duration, tasks[i].des_task);
                }
                else
                    ListsTaks_Order(v);

                break;
            case 'n':
                BreakStr_Requ(str, v, INST_N);

                n = atoi(v[1]);
                if (n == 0) printf("%d\n", time);
                else
                {
                    AdvanceTime(n);
                    printf("%d\n", time);
                }

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
                BreakStr_Requ(str, v, INST_M);
                if (MoveError(v) == 0)
                    MoveTask(v);
                break;
            case 'd':
                break;
            case 'a':
                BreakStr_Opt(str, "\n", v);

                if (v[1] == NULL)
                {
                    for (i = 0; i < act_number; i++)
                        printf("%s\n", activities[i].des_act);
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