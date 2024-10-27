#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <limits.h>
int main()
{
    int k, i;
    scanf("%d", &k);
    long int a1=1, a2=1, a3;
    switch (k){
    case 1:
        printf("%3d  %d\n",1,1);
        break;
    case 2:
        printf("%3d  %d\n",1,1);
        printf("%3d  %d\n",2,1);
        break;
    default:
        printf("%3d  %d\n",1,1);
        printf("%3d  %d\n",2,1);
        for (i = 3; i <= k & i <= 32; i++)
        {
            a3 = a2 + 2*a1;
            printf("%3d  %d\n",i,a3);
            a1 = a2;
            a2 = a3;
        }
        break;
    }
    a1 = 1; a2 = 1; i = 2;
    while ((a1 <= LONG_MAX - a1) & (a1 + a1 <= LONG_MAX - a2))
    {
        a3 = a2 + 2*a1;
        a1 = a2;
        a2 = a3;
        i++;
    }
    printf("\n%3d  %d\n",i-2,(a2-a1)/2);
    printf("%3d  %d\n",i-1,a1);
    printf("%3d  %d\n",i,a2);

}
