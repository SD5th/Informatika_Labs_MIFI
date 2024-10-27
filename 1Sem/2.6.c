#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

void fill_array(int a, int b, int *arr, int size)
{
    int* end = arr + size - 1;
    do
        *arr = a * ((arr-end) + size + b - 1);
    while (arr++ != end);
}
void show_array(int *begin, int *end)
{
    int* a;
    for (a = begin; a <= end; a++){
        printf("%5d", a - begin + 1);
    }
    printf("\n");
    for (a = begin; a <= end; a++){
        printf("%5d", *a);
    }
    printf("\n");
}
void swap_array(int *ar1_last, int *ar2_first, int k)
{
    int temp;
    int* ukaz1 = ar1_last - k + 1;
    int* ukaz2 = ar2_first;
    for (int i = 0; i < k; i++)
    {
        temp = *ukaz1;
        *ukaz1 = *ukaz2;
        *ukaz2 = temp;
        ukaz1++; ukaz2++;
    }
}
int main()
{
    int m1[8], m2[12];
    int a, b, k;
    scanf("%d %d", &a, &b);
    fill_array(a, b, m1, 8);
    scanf("%d %d", &a, &b);
    fill_array(a, b, m2, 12);
    scanf("%d", &k);
    show_array(m1, m1 + 7);
    printf("\n");
    show_array(m2, m2 + 11);
    printf("\n");

    swap_array(m1+7, m2, k);

    swap_array(m2+11, m1, k);

    swap_array(m1+7, m1, k);


    show_array(m1, m1 + 7);
    printf("\n");
    show_array(m2, m2 + 11);


}