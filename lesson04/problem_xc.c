/*
Problem XC — подсчёт коллизий в хеш-функции
Ваша задача: имея произвольную функцию хеширования строки и произвольную последовательность
строк, подсчитать количество коллизий

typedef int (*get_hash_t)(const char *s);

// подсчитать количество коллизий функции f над
// массивом strs
int ncollisions(char **strs, int n, get_hash_t f);
Вы можете быть уверены, что значение хеша для каждой из строк не больше чем заданная наперед
константа HASH_MAX

В посылке должна быть только указанная функция, отправлять функцию main не нужно


Пример 1

Входная функция: сумма кодов символов

Входной массив: "ad", "bc"

Выход: 1 (bc имеет такую же сумму кодов и таким образом является коллизией)
*/

#ifdef NDEBBUG
#include <stdio.h>
#include <string.h>

#define HASH_MAX 10000

typedef int (*get_hash_t)(const char *s);

int scancodes(const char* str)
{
    int sum = 0;

    for (int i = 0; i < strlen(str); ++i)
        sum += str[i];

    return sum;
}
#endif

// подсчитать количество коллизий функции f над
// массивом strs
int ncollisions(char **strs, int n, get_hash_t f)
{
    int collisions = 0;
    char badhash[HASH_MAX] = {0};

    for (int i = 0; i < n; ++i)
    {
        int hash = f(strs[i]);

        if (badhash[hash])
            ++collisions;
        else
            badhash[hash] = 1;
    }

    return collisions;
}

#ifdef NDEBBUG
int main()
{
    char *str[] = {"ad", "bc", "def", "jam", "fed", "edf"};
    printf("%d\n", ncollisions(str, sizeof(str) / sizeof(char*), scancodes));
}
#endif