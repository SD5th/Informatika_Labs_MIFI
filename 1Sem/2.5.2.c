#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>


int main()
{
    unsigned long int n, m;
    scanf("%d %d", &n, &m);
    unsigned long int n1 = n % 2, m1 = m % 2;
    unsigned long int s = n1 + m1;
    if (s % 2 == 0)
    {
        if (n < m)
            printf ("%d", n);
        else
            printf ("%d", m);
    }
    else
        printf ("endless");
    printf("\n");
    
}