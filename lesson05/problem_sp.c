/*
Problem SP — замена в строке
Ваша задача написать функцию с наперёд заданным прототипом, осуществляющую замену всех
подстрок в строке

char *replace(char *str, char const *from, char const *to);
Функция должна аллоцировать и возвращать строку со всеми вхождениями from, замененными на to

Посылка должна состоять из этой одной функции (допустимо также любое количество
вспомогательных), и не должна содержать функции main

Пример 1

Вход: "Hello, %username, how are you, %username", "%username", "Eric, the Blood Axe"

Выход: "Hello, Eric, the Blood Axe, how are you, Eric, the Blood Axe"
*/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

int substrcount(const char* haystack, const char* needle)
{
    int res = 0, len = strlen(needle);
    const char *from = haystack;
    char *found;

    while (found = strstr(from, needle))
    {
        ++res;
        from = found + len;
    }

    return res;
}

char *replace(char *str, char const *from, char const *to)
{
    int dsize = strlen(to) - strlen(from);
    int count = substrcount(str, from);
    int new_size = strlen(str) + count * dsize;
    char *res, *str_it = str, *res_it, *next_replace;

    if (!count)
        return str;
    
    res = calloc(new_size + 1, sizeof(char));
    if (!res)
    {
        fprintf(stderr, "Calloc error");
        abort();
    }

    res_it = res;
    
    while ( next_replace = strstr(str_it, from), next_replace != 0 )
    {
        while (str_it < next_replace)
            *(res_it++) = *(str_it++);

        for (int i = 0; i < strlen(to); ++i)
            *res_it++ = to[i];
    
        str_it += strlen(from);
    }

    while (*str_it)
         *res_it++ = *str_it++;

    *res_it = 0;

    return res;
}

#ifdef NDEBUG
int main()
{
    char *str, *res;
    char template[] = "Hello, %username, how are you, %username";
    char from[] = "%username"; 
    char to[] = "Eric, the Blood Axe";

    str = calloc(strlen(template) + 1, sizeof(char));
    strcpy(str, template);

    printf("b4: %s %lu\n", str, strlen(str));

    res = replace(str, from, to);
    if (!res)
    {
        fprintf(stderr, "Replace error");
        free(str);
        abort();
    }

    printf("aftr: %s %lu\n", res, strlen(res));

    free(res);
}
#endif