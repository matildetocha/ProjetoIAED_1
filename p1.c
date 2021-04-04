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
/* qual é o número máximo de instruções que o sitema aceita?? */
#define MAX 100

typedef struct
{
    char des_user[SZ_DES_UA];
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

Task tasks[10000];

void adiciona_tarefa() {
    Task t;
    t.identifier = 0;
    t.task_user = NULL;
    tasks[0] = t;
}

int main()
{
    strcpy(activities[0].des_act, "TO DO");
    strcpy(activities[0].des_act, "TO DO");
    strcpy(activities[0].des_act, "TO DO");

    char str[MAX];
    int c;

    while ((c = getchar()) != 'q')
    {
        getchar();
        fgets(str, MAX, stdin);

        switch (c)
        {
        case 't':
            adiciona_tarefa()
            break;
        case 'l':
            break;
        case 'n':
            break;
        case 'u':
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