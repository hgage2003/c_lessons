/*
Homework HWK — алгоритм КМП
Ваша задача:

Написать функцию patpreproc, которая препроцессирует паттерн, чтобы далее использовать алгоритм
Кнута-Морриса-Пратта

Написать функцию strstrci с наперёд заданным прототипом, которая ищет подстроку в строке,
независимо от регистра символов (ci означает case insensitive)

void patpreproc(char const * needle, int * needle_lps);
char * strstrci(char const * needle, int const * needle_lps, char const * haystack);
Ниже приведён пример применения

char const *needle = "Ab", *src = "abracadaBra";
char *pos1, *pos2, *pos3; 
pos1 = strstrci(needle, src);
assert(pos1 != NULL);
pos2 = strstrci(needle, pos1 + 2);
assert(pos2 != NULL);
pos3 = strstrci(needle, pos2 + 2);
assert(pos3 == NULL);
Первая найденная позиция "abracadabra", вторая "abracadaBra"

В этой задаче простой и наивный алгоритм из Problem SU не пройдёт тесты, так как в тестах есть
гигантские строки
*/

#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

void patpreproc(char const * needle, int * needle_lps)
{
    for (int i = 1; i < strlen(needle); ++i)
    {
        int k = needle_lps[i - 1];
        
        while ((k > 0) && (tolower(needle[k]) != tolower(needle[i])))
            k = needle_lps[k - 1];

        if (tolower(needle[k]) == tolower(needle[i]))
            ++k;
        
        needle_lps[i] = k;
    }
}

char *strstrci(char const * needle, int const * needle_lps, char const * haystack)
{
    int ndl_len = strlen(needle), hay_len = strlen(haystack), k = 0;
    char *result = NULL;

    for (int i = 0; i < hay_len; ++i)
    {
        while ((k > 0) && (tolower(needle[k]) != tolower(haystack[i])))
            k = needle_lps[k - 1];

        if (tolower(haystack[i]) == tolower(needle[k]))
            ++k;

        if (k == ndl_len)
        {
            return (char*)&haystack[i - k + 1];
        }
    }

    return NULL;
}

#ifdef NDEBUG
int main()
{
    char const *needle = "aBc", *src = "abcdabcabcdabcdab";
    char *pos1, *pos2, *pos3;
    int *lps = calloc(strlen(needle), sizeof(int));
    patpreproc(needle, lps);

    pos1 = strstrci(needle, lps, src);
    if (pos1)
        printf("%s\n", pos1);
    else
        printf("none\n");

    pos1 = strstrci(needle, lps, pos1 + 1);
    if (pos1)
        printf("%s\n", pos1);
    else
        printf("none\n");

    pos1 = strstrci(needle, lps, pos1 + 1);
    if (pos1)
        printf("%s\n", pos1);
    else
        printf("none\n");

    free(lps);
}
#endif