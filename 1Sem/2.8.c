#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

void show_array(int *begin, int *end)
{
    int* a;
    for (a = begin; a <= end; a++){
        printf("%3d", a - begin + 1);
    }
    printf("\n");
    for (a = begin; a <= end; a++){
        printf("%3d", *a);
    }
    printf("\n");
}

void swap_i_last(int *begin, int *end, int i)
{
    int temp; 
    i = i - 1;
    temp = *end;
    *end = *(begin+i);
    *(begin+i) = temp;
}
void add_unit(int *array, int size, int a, int k)
{
    array = realloc(array, (size+1)*sizeof(int));
    for (int i = size; i > k-1; i = i - 1)
        *(array+i) = *(array+i-1);
    *(array+k-1) = a;
}
int main()
{
    int n, i, a, k;
    int* arr;
    scanf("%d", &n);
    arr = malloc(n*sizeof(int));
    if (arr == NULL)
    {
        printf("Memory net\n");
        exit(EXIT_FAILURE);
    }
    for (int j = 0; j < n; j++)
        scanf("%d", (arr+j));
    scanf("%d %d %d", &i, &a, &k);
    show_array(arr, arr+n-1);
    swap_i_last(arr, arr+n-1, i);
    add_unit(arr, n, a, k);
    printf("\n");
    show_array(arr, arr+n);
    free(arr);
}