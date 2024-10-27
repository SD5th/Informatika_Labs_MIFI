#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>


char * read_string(char * str, int * size_out)
{
    int size = 1;
    str = malloc(sizeof(char));
    if (str == NULL)
    {
        printf("Net memory\n");
        exit(EXIT_FAILURE);
    }
    *(str+size-1) = getchar();
    while (*(str+size-1)!='\n')
    {
        size++;
        str = realloc(str, sizeof(char)*size);
        if (str == NULL)
        {
            printf("Net memory\n");
            exit(EXIT_FAILURE);
        }
        *(str+size-1) = getchar();
    }
    *size_out = size;
    //printf("%s", str);
    return str;
}
void empty(char * str, int str_size)
{
    for (int i = 0; i < str_size - 1; i++)
        *(str+i) = ' '; 
    *(str + str_size - 1) = '\n';
}
int main()
{
    char * str;
    int str_size = 0;
    str = read_string(str, &str_size);
    char * buf = malloc(sizeof(char) * str_size);
    empty(buf, str_size);
    int kolvo = 0, tsifri = 0;
    for (int i = 0; i < str_size; i++)
    {
        if (*(str+i) > 47 && *(str+i) < 58)
            {
                *(buf+i) = *(str+i);
                tsifri++;
            }
        else
            if (tsifri != 0)
            {
                kolvo++;
                tsifri = 0;
                printf("%d\n", atoi(buf));
                empty(buf, str_size);
            }
    }
    if (tsifri != 0)
    {
        kolvo++;
        printf("%d\n", atoi(buf));
        empty(buf, str_size);
    }
    printf("\n%d\n", kolvo);
    free(str);
    free(buf);
}