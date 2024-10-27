#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "Rus");
    int a,b, sum;
    scanf("%d",&a);
    b=a;
    if ((a<1000)||(a>9999))
        printf("wrong number\n");
    else{
        sum = (a%10)+((a=a/10)%10)+((a=a/10)%10)+((a=a/10)%10);
        printf("%d\n",b%sum);
    }
}
