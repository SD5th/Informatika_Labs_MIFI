#include <stdio.h>
#include <math.h>
int main(){
    double S = 0.0, cor = 0.0, Scor = 0.0, f, fcor, x;
    double def_S = 0.0, def_f;
    for (double n = 20000000; n <= 200000000; n += 20000000)
    {
        for (double j = n + 1 - 20000000; j <= n; j++)
        {
            x = pow(j,3);
            f = sqrt((1+sqrt(j)+3*x)/(3+pow(cos(j), 2) + sqrt(j)+x));
            fcor = f - cor;
            Scor = S + fcor;
            cor = (Scor - S) - fcor;
            S = Scor;

            def_f = f;
            def_S += def_f;
        }
        printf ("%9.0f%18.4f%18.4f%10.4f\n", n, def_S, S, def_S-S);
    }
    return 0;
}

/*
double func(double x)
{
    return 2 * pow(x, 3) - 9 * pow(x, 2) - 60 * x + 1;
}


    double l=5, r=10, fl, fr, fm;
    while (abs(l-r)>=1e-8){
        r = (l+r)/2;
    else


*/
