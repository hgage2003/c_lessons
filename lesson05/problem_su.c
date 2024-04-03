/*
Problem SU — поиск в строке независимо от регистра
Ваша задача написать функцию strstrci с наперёд заданным прототипом, которая ищет подстроку в
строке, независимо от регистра символов (ci означает case insensitive)

char * strstrci(char const * needle, char const * haystack);
Ниже приведён пример применения

char const *needle = "Ab", *src = "abracadaBra";
char *pos1, *pos2, *pos3; 
pos1 = strstrci(src, needle);
assert(pos1 != NULL);
pos2 = strstrci(pos1 + 2, needle);
assert(pos2 != NULL);
pos3 = strstrci(pos2 + 2, needle);
assert(pos3 == NULL);
Первая найденная позиция "abracadabra", вторая "abracadaBra"

Вы можете реализовать простой и наивный алгоритм с квадратичной асимптотической сложностью, он
пройдёт тесты к этой задаче
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

char * strstrci(char const * needle, char const * haystack)
{
    unsigned hlen = strlen(haystack), nlen = strlen(needle);
    const char *from = haystack;

    for (int i = 0; i < hlen - nlen; ++i)
    {
        char same = 1;
        for (int j = 0; j < nlen; ++j)
        {
            if (tolower(haystack[i + j]) != tolower(needle[j]))
            {
                same = 0;
                break;
            }
        }
        if (!same)
            continue;
        
        return (char*)&haystack[i];
    }

    return NULL;
}

#ifdef NDEBUG
int main()
{
    char const *needle = "bvbjq"; 
    char const *src = "gAmdGIUFhsQgvpLqlaCfpFIvpoGNwpntHLBszLcimPEeduOvFvUgCMHRBvBjqQvGKNmAyiuZIYGZZxOXbKfKrYjdfnrHVGRKTEhOIvYxIcMkqeDUQKvjejoAeAvkctNkXeVhBhGFVWJdovCUnoMrgcQPmQPVVVxpjAKZBJaIkCTssErdWylozZsYHiVnFitKIlsfxdtX";
    char *pos;
    pos = strstrci(needle, src);
    printf("%s\n", pos);
}
#endif