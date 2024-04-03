/*
Problem SA — конкатенировать с реаллокацией
Ваша задача написать функцию с наперёд заданным прототипом, осуществляющую конкатенацию
строк с реаллокацией

char *strcat_r(char *dest, const char *src, int *bufsz);
Функция должна дописывать src в конец dest, при необходимости реаллоцируя dest

Параметр bufsz содержит фактический размер массива для dest, который может быть куда больше, чем
её null-terminated длина. Это in-out параметр, так как туда записывается новый размер. Функция должна,
если буфер недостаточен, реаллоцировать его точно до размера сконкатенированной строки, делать
запас для амортизации не надо

Возвращаемое значение: указатель на начало сконкатенированной строки. Из-за реаллокаций он может
и не совпадать с dest

Посылка должна состоять из этой одной функции (допустимо также любое количество
вспомогательных), и не должна содержать функции main

Пример 1

Вход: "Hello", 6, ", world!"

Выход: "Hello, world!"
*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

char *strcat_r(char *dest, const char *src, int *bufsz)
{
    int res_len;
    char *res;

    res_len = strlen(dest) + strlen(src);

    if (res_len < *bufsz) // не <= из-за нуля в конце
    {
        return strcat(dest, src);
    }
    
    res = (char*)realloc(dest, res_len + 1);
    if (res)
        strcat(res, src);
    
    *bufsz = res_len + 1;
    return res;    
}

#ifdef NDEBUG
int main()
{
    char *buff, *res;
    int buff_size = 9;

    buff = calloc(buff_size, sizeof(char));
    strcpy(buff, "This is ");

    res = strcat_r(buff, "a simple text", &buff_size);
    if (!res)
    {
        fprintf(stderr, "Error in strcat_r");
        free(buff);
        abort();
    }

    printf("%s %d\n", buff, buff_size);

    free(buff);
}
#endif