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



void Merge(int* first, int* last)
{
    int* B; /*вспомогательный массив*/
    B = (int*) malloc(sizeof(int) * (last-first+1));
    if (B == NULL)
    {
        printf("Memory not videlena\n");
        exit(EXIT_FAILURE);
    }
    int k = 0; /*индекс во вспомогательном массиве*/
    int * m; /*указатель на средний элемента*/
    m = first + (last-first)/2;
    int * l; /*левый указатель*/
    l=first; 
    int * r; /*правый указатель*/
    r = m+1;
    while (l<=m && r<=last) {   /* Пока не закончился */
        if (*l<=*r) {           /* хотя бы один фрагмент,*/
           B[k]=*l; l++;       /* заполняем вспомогательный массив.*/
        }
        else {
           B[k]=*r; r++; 
        }
        k++; 
    }   /*Один из фрагментов закончился.*/
       /*Переносим остаток другого фрагмента во вспомогательный массив.*/
    while (l<=m) {
       B[k]=*l; l++; k++; 
    }
    while (r<=last) {
       B[k]=*r; r++; k++; 
    }
    for (l=first; l<first+k; l++)
       *l=B[l-first];
    free(B);
}

void MergeSort(int * first, int * last, int *first_global, int * last_global)
{
    int * m; /*индекс среднего элемента*/
    if (first<last)
        if (last-first==1) {
            if (*last < *first)
                swap(first, last);
        }
        else {
            m=first+(last-first)/2;
            MergeSort(first,m, first_global, last_global);
            MergeSort(m+1,last, first_global, last_global);
            Merge(first,last);
            print_arr(first_global, last_global); printf("\n");
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
    MergeSort(arr, arr+size-1, arr, arr+size-1);
}