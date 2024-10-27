#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

void swap (int *a, int *b)
{
    int temp = *a;
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

void QuickSort(int* first, int* last, int* first_global, int* last_global)
 {
    int pivot; /*опорное значение*/
    int l = first - first_global, r = last - first_global; /*левый и правый счетчики*/
    pivot = *(first_global+ (int) ((l+r)/2)); /*определение опорного значения*/
    while (l<r) {
        while (*(first_global+l)<pivot) l++;
        while (*(first_global+r)>pivot) r--;
        if (l<r) {
            swap(first_global+l, first_global+r); /*перестановка двух элементов*/
            printf("%d\n", pivot);
            print_arr(first_global, last_global);
            printf("\n");
        }
 } /*Рекурсивная сортировка:*/
    if (first < first_global + l - 1) 
        QuickSort(first, first_global + l - 1, first_global, last_global); /*- левого участка, */
    if (first_global + r + 1 < last) 
        QuickSort(first_global + r + 1, last, first_global, last_global); /*- правого участка.*/
 }

 
int main()
{
    int size, kolvo_sravn = 0, kolvo_prisv = 0;
    int * arr;
    scanf("%d", &size);
    arr = (int*) malloc(sizeof(int)*size);
    for (int i = 0; i < size; i++)
        scanf("%d", arr+i);
    QuickSort(arr, arr+size-1, arr, arr+size-1);
    print_arr(arr, arr+size-1);
}