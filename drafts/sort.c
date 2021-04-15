#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define maxN 10000

typedef int Item;
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

Item aux[maxN];

void MergeStr(char *a[], int ids[], int l, int m, int r)
{
    int i, j, k, ax_ids[maxN];
    char *ax[maxN];

    for (i = m + 1; i > l; i--)
    {
        ax[i - 1] = a[i - 1];
        ax_ids[i - 1] = ids[i - 1];
    }
    for (j = m; j < r; j++)
    {
        ax[r + m - j] = a[j + 1];
        ax_ids[r + m - j] = ids[j + 1];
    }
    for (k = l; k <= r; k++)
    {
        if (strcmp(ax[j], ax[i]) < 0)
        {
            a[k] = ax[j];
            ids[k] = ax_ids[j--];
        }
        else
        {
            a[k] = ax[i];
            ids[k] = ax_ids[i++];
        }
    }
}

void MergeInt(Item a[], int l, int m, int r)
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

void MergeSort(char *a[], int ids[], int l, int r)
{
    int m = (r + l) / 2;
    if (r <= l)
        return;
    MergeSort(a, ids, l, m);
    MergeSort(a, ids, m + 1, r);
    MergeStr(a, ids, l, m, r);
}

int main()
{
    char *b[maxN] = {"nuno", "luís", "alexandre", "ana", "raquel", "beatriz", "matilde"};
    int ids[maxN] = {1, 2, 3, 4, 5, 6, 7};
    int i;

    MergeSort(b, ids, 0, 6);
    for (i = 0; i < 7; i++)
        printf("%d %s\n", ids[i], b[i]);
    return 0;
}