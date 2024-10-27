#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
int main()
{
    int m;
    scanf("%d", &m);
    if (3 < m)
    {
        int k = 1, current = 3;
        while (current < m)
        {
            k++;
            current *= 3;
        }
        printf("%d\n", k-1);
    }
    else
        printf("0\n");

}
