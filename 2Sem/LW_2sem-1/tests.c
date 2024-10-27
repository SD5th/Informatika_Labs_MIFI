#include "My_String.c"

int main(){
    String str1, str2, str_orig;

    str1.size = 5;
    str1.chars = malloc(5*sizeof(char));
    str1.chars[0] = '1'; str1.chars[1] = '2'; str1.chars[2] = '3'; str1.chars[3] = '4'; str1.chars[4] = '5';
    
    str2.size = 3;
    str2.chars = malloc(3*sizeof(char));
    str2.chars[0] = 'a'; str2.chars[1] = 'b'; str2.chars[2] = 'c';
    
    str_orig.size = 7;
    str_orig.chars = malloc(7*sizeof(char));
    str_orig.chars[0] = 'A'; str_orig.chars[1] = 'b'; str_orig.chars[2] = 'c'; str_orig.chars[3] = '1';
    str_orig.chars[4] = '2'; str_orig.chars[5] = '3'; str_orig.chars[6] = '!'; 


    // Тест конкатенации
    printf("\nCONCATENATION TEST\n");
    
    String str_concat;
    str_concat = string_concat(str1, str2);

    printf("\nFirst  string: 12345 \nFirst  size: 5\n");
    printf("\nSecond string: abc \nSecond size: 3\n");
    printf("\nExpec. string: 12345abc\nExpec. size: 8 \n");
    printf("\nReal   string: "); string_print(str_concat);
    printf("\nReal   size: %d\n\n", str_concat.size);
    
    if ((str_concat.size == 8) 
      & (str_concat.chars[0] == '1') & (str_concat.chars[4] == '5') 
      & (str_concat.chars[1] == '2') & (str_concat.chars[5] == 'a')
      & (str_concat.chars[2] == '3') & (str_concat.chars[6] == 'b')
      & (str_concat.chars[3] == '4') & (str_concat.chars[7] == 'c'))
        printf("Concatenation OK");
    else
        printf("Concatenaion Wrong");
    
    printf("\n\n------------------\n");
    
    // Тест получения подстроки
    printf("\nGET SUBSTRING TEST\n");
    String str_sub;
    str_sub = string_get_sub(str1, 1, 3);

    printf("\nOriginal string: 12345 \nOriginal size: 5"
           "\nLeft border: 1; Right border: 3\n"
           "\nExpected string: 234 \nExpected size: 3\n"
           "\nResult   string: "); string_print(str_sub);
    printf("\nResult   size: %d\n\n", str_sub.size);

    if ((str_sub.size == 3) 
      & (str_sub.chars[0] == '2') & (str_sub.chars[1] == '3') & (str_sub.chars[2] == '4'))
       printf("Get substring OK");
    else
        printf("Get substring Wrong");
    printf("\n\n------------------\n");
    
    // Тест перекодирования строки
    printf("\nRECODE STRING TEST\n");
    String str_recode;
    int * keys;
    keys[0] = -2;
    str_recode = string_recode(str_orig, Caesar_cipher, keys);

    printf("\nOriginal string: Abc123! \nOriginal size: 7"
           "\nRecoding algorithm: Caesar cipher"
           "\nShift: -2\n"
           "\nExpected string: Yza901! \nExpected size: 7\n"
           "\nResult   string: "); string_print(str_recode);
    printf("\nResult   size: %d\n\n", str_recode.size);

    if ((str_recode.size == 7) 
      & (str_recode.chars[0] == 'Y') & (str_recode.chars[4] == '0') 
      & (str_recode.chars[1] == 'z') & (str_recode.chars[5] == '1')
      & (str_recode.chars[2] == 'a') & (str_recode.chars[6] == '!')
      & (str_recode.chars[3] == '9'))
        printf("Recoding OK");
    else
        printf("Recoding Wrong");
    printf("\n\n------------------\n");



    free(str1.chars);
    free(str2.chars);
    free(str_orig.chars);
    free(str_concat.chars);
    free(str_sub.chars);
    free(str_recode.chars);
}
