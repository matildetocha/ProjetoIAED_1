/*
 * File:  structures.c
 * Author:  Matilde Tocha 99108
 * Description: Programa com as três estruturas relevantes para o projeto. Tarefa, atividade e utilizador.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* Número máximo de caracteres para descrever um utilizador ou uma atividade */
#define SZ_DES_UA 21
/* Número máximo de caracteres para descrever uma tarefa */
#define SZ_DES_T 51
/* Número máximo de utilizadores que o sistema suporta */
#define SZ_USERS 51
/* Número máximo de tarefas que o sistema suporta */
#define SZ_TASKS 10000
/* qual é o número máximo de instruções que o sitema aceita?? */
#define MAX 100

typedef struct
{
    char des_user[SZ_DES_UA];
    int user_number;
} User;

User system_users[SZ_USERS];

typedef struct
{
    char des_act[SZ_DES_UA];

} Activity;

Activity activities[10];

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

void AddUser(User v)
{
    int i = 0;

    for (i = 0; i < SZ_USERS; i++)
    {
        if (strcmp(v.des_user, system_users[i].des_user) == 0)
            printf("user already exists\n");
    }
    printf("%ld\n", strlen(system_users->des_user));
    if (strlen(system_users->des_user) == SZ_USERS)
        printf("too many users\n");
    else
        strcpy(system_users[v.user_number].des_user, v.des_user);
}

int main()
{
    char str[MAX];
    int c;
    int i = 0;
    User u;

    strcpy(activities[0].des_act, "TO DO");
    strcpy(activities[1].des_act, "IN PROGRESS");
    strcpy(activities[2].des_act, "DONE");
    strcpy(system_users[0].des_user, "PedroMariaSilva");
    strcpy(system_users[1].des_user, "abc");

    while ((c = getchar()) != 'q')
    {
        getchar(); /* Retira o carácter em branco entre o comando e as devidas instruções */
        fgets(str, MAX, stdin);

        switch (c)
        {
        case 't':
            break;
        case 'l':
            break;
        case 'n':
            break;
        case 'u':
            if (1)
            {
                strcpy(u.des_user, strtok(str, " \n"));
                u.user_number++;
                AddUser(u);
            }
            for (i = 0; i < SZ_USERS; i++)
                printf("%s\n", system_users[i].des_user);
            break;
        case 'm':
            break;
        case 'd':
            break;
        case 'a':
            break;
        }
    }

    exit(EXIT_SUCCESS);
}