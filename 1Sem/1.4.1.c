#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    int arr[40];
    int a, *k, sum = 0, kolvo = 0, vsego = 0, min = 10000, kolvom = 0;
    double m;
    /*
    int stime, rmin, rmax;
    long int ltime;
    ltime=time(NULL); stime=(unsigned) ltime/2; srand(stime);
    scanf("%d %d", &rmin, &rmax);
    for (k = arr; k < arr+40; k++){
        *k = (rand()%(rmax-rmin+1))+rmin;
        printf("%d %d", arr-k, *k);
    }
    */
    for (k = arr; k < arr + 40; k++)
        scanf("%d", k);
    scanf("%d", &a);
    for (k = arr; k < arr + 40; k++)
        if (*k > a)
        {
            sum += *k;
            kolvo++;
        }
    m = (double)sum / (double)kolvo;
    for (k = arr; k < arr + 40; k++)
    {
        if (*k > m)
        {
            vsego++;
            if (*k == min)
                kolvom++;
            if (*k < min)
            {
                min = *k;
                kolvom = 1;
            }
        }
    }
    printf("%.4f\n%d\n%d %d\n", m, vsego, min, kolvom);
}
