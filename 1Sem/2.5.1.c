#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void point(int k1, int b1, int k2, int b2, double *x, double *y)
{
    *x = (double) (b2-b1) / (double) (k1-k2);
    *y = (double) (k1) * *x + (double) b1;
}
int main()
{
    int k1, b1, k2, b2, code = 0;
    double x, y;
    scanf ("%d %d %d %d", &k1, &b1, &k2, &b2);
    if (k1 == k2)
        if (b1 == b2)
            code = 2;
        else 
            code = 1;
    else {
        if ((k1 == 0) || (k2 == 0))
            code = 3;
        point(k1, b1, k2, b2, &x, &y);
    }
    printf("%d\n", code);
    if (code == 0 || code == 3)
        printf("%.6f\n%.6f\n", x, y);
}