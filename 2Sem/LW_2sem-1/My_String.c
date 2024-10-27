#include <stdio.h>
#include <stdlib.h>

// Объявление структуры String (строки).
typedef struct {                        
    char* chars;                        // Поле, в котором хранятся символы строки.
    int size;                           // Поле, в котором хранится размер строки.
} String;

// Функция для проверки, прошло ли выделение памяти успешно.
void NULL_check (void* p)
{              
    if (p == NULL)                      // Проверка, соответствует ли указателю p место в памяти. 
    {
        printf("Error: No memory\n"); 
        exit(EXIT_FAILURE);             // Если не соответствует, выходим из программы с ошибкой.
    }
}

// Функция для проверки, можно ли работать со строкой.
void string_valid (String str)     // str – строка, которая будет проверена.
{
    if (str.size < 0)   // Проверка, правильный ли у строки размер. 
    {
        printf("Error: String can't be negative.\n"); 
        exit(EXIT_FAILURE);  
    }
    if ((str.size != 0) & (str.chars == NULL))   // Проверка, равен ли размер пустой строки нулю. 
    {
        printf("Error: Size of empty stringg can't be more than a zero.\n"); 
        exit(EXIT_FAILURE);  
    }
}

// Функция для ввода строки из консоли.
void string_scan(String* str)           // str — адрес строки, которую нужно заполнить.    
{                     
    (*str).size = 0;                    // size = 0 — пустая строка.
    (*str).chars = NULL;                // chars = NULL — пустая строка.            
    char ch;
    ch = getchar();                     // Считывание первого символа строки.
    
    while (ch !='\n')                   // "пока считанный символ не знак перевода строки"
    {
        (*str).size++;
        (*str).chars = realloc((*str).chars, sizeof(char)*(*str).size); // Выделение памяти для строки длины str.size.
        NULL_check((*str).chars);       // Проверка, прошло ли выделение памяти успешно.
        
        *((*str).chars + (*str).size - 1) = ch; //присвоение значения ch последнему слоту str.chars
        ch = getchar();                 // Считывание нового символа строки.
    }
}

// Функция для вывода строки в окно консоли.
void string_print(String str)           // str — строка, которую нужно вывести.      
{
    string_valid(str);                  // Можно ли работать со строкой.
    for (int i = 0; i < str.size; i++)
        printf("%c", *(str.chars+i));   // Выводим str.chars посимвольно.
}

// Функция для объединения строк.
String string_concat(String str_l, String str_r)  // str_l — левая строка, str_l — правая строка
{
    string_valid(str_l); string_valid(str_r);   // Можно ли работать со строками.
    
    String str_out;
    str_out.size = str_l.size + str_r.size;       
    
    if (str_out.size == 0){             // Если str1 и str2 пустые, то str_out тоже пустая строка.
        str_out.chars = NULL;                       
        return str_out;
    }                      

    str_out.chars = malloc(sizeof(char) * str_out.size);
    NULL_check(str_out.chars);          // Проверка, прошло ли выделение памяти успешно.

    for (int i = 0; i < str_l.size; i++) // Перекопирование левой строки.
        str_out.chars[i] = str_l.chars[i];
    for (int i = 0; i < str_r.size; i++) // Перекопирование правой строки.
        str_out.chars[(str_l.size) + i] = str_r.chars[i];
    return str_out;
}

// Функция для получения подстроки.
String string_get_sub (String str_orig, int l, int r)   // str_orig — из неё будет взята подстрока с индекса l по индекс r.
{
    string_valid(str_orig);
    if ((r < l) || (l < 0) || (str_orig.size-1 < r)){   // Проверка, правильные ли l и r.
        printf("Error: Wrong combination of borders.\n");     
        exit(EXIT_FAILURE);
    }

    String str_out;
    str_out.size = r - l + 1;
    str_out.chars = malloc(sizeof(char) * str_out.size);
    NULL_check(str_out.chars);          // Проверка, прошло ли выделение памяти успешно.
    
    for (int i = l; i <= r; i++)        // Перекопирование строки.
        str_out.chars[i-l] = str_orig.chars[i];

    return str_out;
}

// Образец функции перекодирования символа
// char %any%_cipher (char orig, int * keys){
//     keys[] – ключи для кодирования.
//     orig – символ, который будет перекодирован
//     char result;
//      /////
//      алгоритм кодирования
//      /////
//     return result;
// }

// Пример функции перекодирования символа, Шифр Цезаря (для цифр и латиницы)
char Caesar_cipher(char orig, int * keys)
{ 
    if ((48 <= orig) & (orig <= 57)){ // Сдвиг цифры на keys[0].
        char result;
        result = (orig - 48 + keys[0]) % 10;
        return (result >= 0) ? (result + 48) : (10 + result + 48);
    }

    if ((65 <= orig) & (orig <= 90)){ // Сдвиг заглавной буквы на keys[0].
        char result;
        result = (orig - 65 + keys[0]) % 26;
        return (result >= 0) ? (result + 65) : (26 + result + 65);
    }

    if ((97 <= orig) & (orig <= 122)){// Сдвиг строчной буквы на keys[0].
        char result;
        result = (orig - 97 + keys[0]) % 26;
        return (result >= 0) ? (result + 97) : (26 + result + 97);
    }
    return orig;    // Если символ не оказался цифрой или буквой, возвращаем его назад.
}

// Функция для перекодирования строки.
String string_recode (String str_orig, char (*char_recode)(char, int*), int* keys) // str_orig — строка для перекодирования,
{                                                       // char_recode — функция для перекодирования символа, keys — аргументы для кодирования.
    string_valid(str_orig);
    String result;
    result.size = str_orig.size;
    result.chars = malloc(result.size * sizeof(char));
    for (int i = 0; i < result.size; i++)
        result.chars[i] = char_recode(str_orig.chars[i], keys); // Перекодирование символов поочерёдно.
    return result;
}