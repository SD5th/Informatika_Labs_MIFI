#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

void print_arr(int * arr, int size)
{
    for (int i = 0; i < size; i++)
        printf("%3d", i+1);
    printf("\n");
    for (int i = 0; i < size; i++)
        printf("%3d", *(arr+i));
    printf("\n");
}
void swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void insert_sort(int *arr, int size, int * kolvo_sravn, int *kolvo_prisv)
{
    int i, j, k;
    for (i = 1; i < size; i++)
    {   
        print_arr(arr, size);
        printf("\n");
        for (j = 0; j < i; j++)
        {
            *kolvo_sravn = *kolvo_sravn + 1;
            if (*(arr+j) <= *(arr+i))
            {
                *kolvo_prisv = *kolvo_prisv + 1;
                for (k = i; k > j; k -= 1)
                {
                    swap(arr+k, arr+k-1);
                    *kolvo_prisv = *kolvo_prisv + 2;
                }
                break;
            }
        }
    }
}
int main()
{
    int size, kolvo_sravn = 0, kolvo_prisv = 0;
    int * arr;
    scanf("%d", &size);
    arr = (int*) malloc(sizeof(int)*size);
    for (int i = 0; i < size; i++)
        scanf("%d", arr+i);
    insert_sort(arr, size, &kolvo_sravn, &kolvo_prisv);
    print_arr(arr, size);
    printf("%d %d\n", kolvo_prisv, kolvo_sravn);
}