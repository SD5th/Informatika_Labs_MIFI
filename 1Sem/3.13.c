#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(){
    char str[5];
    int * massiv = (int*) malloc(sizeof(int) * 1);
    int count = 0;
    int sum = 0;
    while (1 == 1)
    {
        scanf("%s", str);
        count++;
        if (str[0] == 'n')
            break;
        if (count > 2){
            realloc(massiv, sizeof(int*) * (count-2));
            if (massiv == NULL) {
                return 0;
            }
            *(massiv+count-3) = atoi(str);
        }
    }
    for (int i = 0; i < count-3; i++)
    {
        sum += *(massiv+i);
        printf("%4d", *(massiv+i));
    }
    printf("\n%d\n", sum);
    
}