#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Worker{
    char name[15];
    char last_name[15];
    int nomer_otdela;
    int oklad;
    int premiya;
    int nalogi;
} wk;

int zp(wk worker)
{
    return worker.oklad + worker.premiya - worker.nalogi;
}

void pr(wk worker){
    printf("%-15s%-15s%5d%5d%5d%5d\n", worker.last_name, worker.name, worker.nomer_otdela, worker.oklad, worker.premiya, worker.nalogi);
}

int main()
{
    int n;
    scanf("%d", &n);
    wk* list;
    list = (wk *) malloc(sizeof(wk) * n);
    int index_worst_worker = -1;
    int min_zp = INT_MAX;

    for(int i = 0; i<n; i++){
        scanf("%s", list[i].last_name);
        scanf("%s", list[i].name);
        scanf("%d", &list[i].nomer_otdela);
        scanf("%d", &list[i].oklad);
        scanf("%d", &list[i].premiya);
        scanf("%d", &list[i].nalogi);
        if((zp(list[i]) < min_zp) && (list[i].nomer_otdela == 1)){
            index_worst_worker = i;
            min_zp = zp(list[i]);
        }
    }

    for(int i = 0; i<n; i++)
        pr(list[i]);

    printf("\n%s %s\n\n", list[index_worst_worker].last_name, list[index_worst_worker].name);

    for(int i = 0; i < n; i++){
        if ((zp(list[i]) <= min_zp) && (index_worst_worker != i) && (list[i].nomer_otdela == 1))
            printf("%s %s\n", list[i].last_name, list[i].name);
    }
}