#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef int Item;
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define equal(A, B) (key(A) == key(B))
#define exch(A, B) { Item t = A; A = B; B = t; }
#define exch_str(A, B) { A = B; }
#define compexch(A, B) if (less(B, A)) exch(A, B)

char *a[500] = {"nuno", "luís", "alexandre", "ana", "raquel", "beatriz", "matilde"}; 

int PartitionStr(int l, int r)
{
    int i = l - 1, j = r, mid = l + (r - l) / 2;
    char v[100];
    if (strcmp(a[mid], a[l]) < 0)
        exch_str(a[mid], a[l]);
    if (strcmp(a[mid], a[r]))
        exch_str(a[mid], a[r]); 
    if (strcmp(a[mid], a[l]))
        exch_str(a[r], a[l]);
    strcpy(v, a[r]); 
    while (i < j)
    {
        while (strcmp(a[++i], v) < 0)
            ;
        while (strcmp(v, a[--j]) < 0)
            if (j == l)
                break;
        if (i < j)
            exch_str(a[i], a[j]);
    }
    exch_str(a[i], a[r]);
    return i;
}

int partition(Item a[], int l, int r)
{
    int i = l - 1, j = r, mid = l + (r - l) / 2;
    Item v;
    if (less(a[mid], a[l]))
        exch(a[mid], a[l]);
    if (less(a[mid], a[r]))
        exch(a[mid], a[r]); /* a[mid] is higher */
    if (less(a[r], a[l]))
        exch(a[r], a[l]);
    v = a[r]; /* mediana */
    while (i < j)
    {
        while (less(a[++i], v))
            ;
        while (less(v, a[--j]))
            if (j == l)
                break;
        if (i < j)
            exch(a[i], a[j]);
    }
    exch(a[i], a[r]);
    return i;
}

void quicksort(Item a[], int l, int r)
{
    int i;
    if (r <= l)
        return;
    i = partition(a, l, r);
    quicksort(a, l, i - 1);
    quicksort(a, i + 1, r);
}
int main()
{
    
    int a[100] = {1, 27, 10, 4, 2, 19, 7, 2, 7};
    int i;

    quicksort(a, 0, 6);
    for (i = 0; i < 7; i++)
        printf("%d\n", a[i]);
    return 0;
}

/* int PartitionStr(int l, int r)
{
    int i = l - 1, j = r, mid = l + (r - l) / 2;
    char v[SZ_DES_UA];
    if (strcmp(aux_tasks[mid].des_task, aux_tasks[l].des_task) < 0)
        MergeAux(mid, l, aux_tasks, aux_tasks);
    if (strcmp(aux_tasks[mid].des_task, aux_tasks[r].des_task))
        MergeAux(mid, r, aux_tasks, aux_tasks);
    if (strcmp(aux_tasks[mid].des_task, aux_tasks[l].des_task))
        MergeAux(r, l, aux_tasks, aux_tasks);
    strcpy(v, aux_tasks[r].des_task); 
    while (i < j)
    {
        while (strcmp(aux_tasks[++i].des_task, v) < 0)
            ;
        while (strcmp(v, aux_tasks[--j].des_task) < 0)
            if (j == l)
                break;
        if (i < j)
            MergeAux(i, j, aux_tasks, aux_tasks);
    }
    MergeAux(i, r, aux_tasks, aux_tasks);
    return i; 
} */

/* int partition(Item a[], int l, int r)
{
    int i = l - 1, j = r, mid = l + (r - l) / 2;
    Item v;
    if (less(a[mid], a[l]))
        exch(a[mid], a[l]);
    if (less(a[mid], a[r]))
        exch(a[mid], a[r]); 
    if (less(a[r], a[l]))
        exch(a[r], a[l]);
    v = a[r]; 
    while (i < j)
    {
        while (less(a[++i], v))
            ;
        while (less(v, a[--j]))
            if (j == l)
                break;
        if (i < j)
            exch(a[i], a[j]);
    }
    exch(a[i], a[r]);
    return i;
} 

void QuickSortTasks(int l, int r)
{
    int i;
    if (r <= l) return;
    i = PartitionStr(l, r);
    QuickSortTasks(l, i - 1);
    QuickSortTasks(i + 1, r);
} 

void Insertion(int l, int r)
{
    int i, j;
    Task v[SZ_DES_UA];
    for (i = l + 1; i <= r; i++)
    {
        MergeAux(i, i, v, aux_tasks);
        j = i - 1;
        while (j >= l && strcmp(v[i].des_task, aux_tasks[j].des_task) < 0)
        {
            MergeAux(j + 1, j, aux_tasks, aux_tasks);
            j--;
        }
        MergeAux(j + 1, j + 1, aux_tasks, v);
    }
    MergeAux(j + 1, j + 1, aux_tasks, v);
} */