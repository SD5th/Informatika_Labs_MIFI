#include <stdio.h>
#include <math.h>
double func(double x)
{
    double k = 2 * pow(x, 3) - 9 * pow(x, 2) - 60 * x + 1;
    if (k > 0)
        return 1;
    return (-1);
}
int main(){
    double l=5.0, r=10.0, m, fl, fr, fm;
    fl = func(l);
    fr = func(r);
    while (r-l>1e-8){
        m = (l+r)/2;
        fm = func(m);
        if (fl == 1)
            if (fm == 1)
                {
                    l = m;
                    fl = fm;
                }
            else {
                r = m;
                fr = fm;
            }
        else
            if (fm == 1){
                r = m;
                fr = fm;
            }
            else{
                l = m;
                fl = fm;
            }
    }
    printf("%.8f\n", m);

}
