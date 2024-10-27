#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int main()
{
    int ** matrix;
    int * mins;
    mins = (int *) malloc(sizeof(int));
    int n, m, min = INT_MAX, kolvo_mins = 0, sedl = -1, kolvo_sedl = 0;
    scanf("%d %d", &n, &m);
    matrix = (int **) malloc(sizeof(int*)*n);
    for (int i = 0; i < n; i++)
        *(matrix+i) = (int *) malloc(sizeof(int)*m);
    for (int i = n-1; i >= 0; i = i - 1)
    {
        if ((n-1-i)%2 == 0)
            for (int j = 0; j < m; j++)
                scanf("%d", *(matrix+i)+j);
        else
            for (int j = m - 1; j >= 0; j = j - 1)
                scanf("%d", *(matrix+i)+j);
    }
    int cur;
    for (int i = 0; i < n; i++)
    {
        cur = 0;
        for (int j = 0; j < m; j++)
            cur += *(*(matrix+i)+j);
        if (cur == min)
        {
            kolvo_mins++;
            mins = (int*) realloc(mins, sizeof(int)*kolvo_mins);
            *(mins + kolvo_mins - 1) = i;
        }
        if (cur < min)
        {
            kolvo_mins = 1;
            mins = (int*) realloc(mins, sizeof(int));
            *(mins + kolvo_mins - 1) = i;
            min = cur;
        }
    }
    int nom_stolb, nom_strok, max;
    for (int i = 0; i < n; i++)
    {
        min = INT_MAX;
        for (int j = 0; j < m; j++)
            if (*(*(matrix+i)+j) < min)
            {
                min = *(*(matrix+i)+j);
                nom_stolb = j;
            }
        max = -1;
        for (int k = 0; k < n; k++)
            if (*(*(matrix+k)+nom_stolb) > max)
            {
                max = *(*(matrix+k)+nom_stolb);
                nom_strok = k;
            }
        if (nom_strok == i)
        {
            if (sedl == min)
                kolvo_sedl++;
            else
            {
                kolvo_sedl = 1;
                sedl = min;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        printf("%3d", **(matrix+i));
        for (int j = 1; j < m; j++)
            printf(" %3d", *(*(matrix+i)+j));
        printf("\n");
    }
    printf("\n");
    printf("%d", *mins+1);
    for (int i = 1; i < kolvo_mins; i++)
        printf(" %d", *(mins+i)+1);
    printf("\n");
    if (kolvo_sedl == 0)
        printf("-\n");
    if (kolvo_sedl == 1)
        printf("%d\n", sedl);
    if (kolvo_sedl > 1)
        printf("%d %d\n", sedl, kolvo_sedl);
}