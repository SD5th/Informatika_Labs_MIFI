#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "Rus");
    int a,b,c, temp;
    scanf("%d %d %d",&a, &b, &c);
    if (b<c)
    {
        temp=c;
        c=b;
        b=temp;
    }
    if (a<b)
    {
        temp=a;
        a=b;
        b=temp;
    }
    if (b<c)
    {
        temp=c;
        c=b;
        b=temp;
    }
    if (a == c)
    {
        printf("%d=%d=%d", a,b,c);
    }
    else if (a == b)
    {
        printf("%d=%d>%d", a,b,c);
    }
    else if (b == c)
    {
        printf("%d=%d<%d", c,b,a);
    }
    else
        printf("%d", b);
    printf("\n");
}
