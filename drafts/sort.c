#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define maxN 10000

typedef char Item;
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch(A, B) \
    Item t = A;    \
    A = B;         \
    B = t;         \
    }
#define compexch(A, B) \
    if (less(B, A))    \
    exch(A, B)

Item *aux[maxN];
void merge(Item *a[], int l, int m, int r)
{
    int i, j, k;
    for (i = m + 1; i > l; i--)
        aux[i - 1] = a[i - 1];
    for (j = m; j < r; j++)
        aux[r + m - j] = a[j + 1];
    for (k = l; k <= r; k++)
        if (less(aux[j], aux[i]))
            a[k] = aux[j--];
        else
            a[k] = aux[i++];
}

/* 
void mergesort(Item *a[], int l, int r)
{
    int m = (r + l) / 2;
    if (r <= l)
        return;
    mergesort(a, l, m);
    mergesort(a, m + 1, r);
    merge(a, l, m, r);
} */

int main()
{
    Item *a[maxN] = {"nuno", "maria", "constança", "carlota", "ana", "joão"};
    int i;

    for (i = 0; i < 6; i++)
        printf("%s\n", a[i]);
    return 0;
}