#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

void swap (int **a, int **b)
{
    int * temp = *a;
    *a = *b;
    *b = temp;
}

void print_arr(int * first, int * last)
{
    for (int * i = first; i <= last; i++)
        printf("%3d", i+1-first);
    printf("\n");
    for (int * i = first; i <= last; i++)
        printf("%3d", *i);
    printf("\n");
}

void print_arr_ukaz(int ** first, int ** last)
{
    for (int ** i = first; i <= last; i++)
        printf("%3d", i+1-first);
    printf("\n");
    for (int ** i = first; i <= last; i++)
        printf("%3d", **i);
    printf("\n");
}



void bubble(int **first, int size)
{
    for (int** i = first+size-1; i > first; i=i-1)
    {
        for (int** j = first; j < i; j++)
        {
            if(**j < **(j+1))
                swap(j, j+1);
        }
    }
}
int main()
{
    int * m1;
    int * m2;
    int ** ans;
    int size1, size2;


    scanf("%d", &size1);
    m1 = (int*) malloc(sizeof(int)*size1);
    if (m1 == NULL)
    {
        printf("Memory not videlena\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size1; i++)
        scanf("%d", m1+i);
        


    scanf("%d", &size2);
    m2 = (int*) malloc(sizeof(int)*size2);
    if (m2 == NULL)
    {
        printf("Memory not videlena\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size2; i++)
        scanf("%d", m2+i);


    ans = (int**)malloc(sizeof(int*)*(size1+size2));
    if (ans == NULL)
    {
        printf("Memory not videlena\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size1; i++)
        *(ans+i) = m1 + i;
    for (int i = size1; i < size1+size2; i++)
        *(ans+i) = m2 + i - size1;

    bubble(ans, size1+size2);
    print_arr(m1, m1+size1-1);
    printf("\n");
    print_arr(m2, m2+size2-1);
    printf("\n");
    print_arr_ukaz(ans, ans+size1+size2-1);
        printf("\n");

}