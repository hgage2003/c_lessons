/*
Homework problem HWH — словарь
На стандартном вводе: количество ожидаемых ответов, длина, текст, разделённый пробелами, длина,
список искомых слов, разделённый пробелами

На стандартный вывод: сколько раз слово из списка слов встретилось в тексте

Пример ввода:

2
27
abc bca abc bac cba bca abc
7
abc bca
В приведённом примере abc встретилось три раза, а слово bca дважды, то есть вывод: 3 2

Тексты для поиска могут быть довольно большими, слов может быть много. Постарайтесь
использовать хеш-таблицы для упрощения подсчёта
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define R 32
#define Q 0x1000

// подсчитать хеш строки от start до fin
int get_hash(const char *start, const char *fin)
{
    int hash = 0, acc = 1;
    assert(fin > start);

    while (fin != start)
    {
        --fin;
        hash = (hash + (*fin) * acc) % Q;
        acc = (acc * R) % Q;
    }
    
    return hash;
}

// обновить хеш current, удалив из него cprev и добавив в него cnext
// здесь n это pow_mod(R, right - 1, Q)
// возвращает новый хеш
int update_hash(int current, int n, char cprev, char cnext)
{
    current = (Q + current - (cprev * n) % Q) % Q;
    current = (current * R + cnext) % Q;

    return current;
}

// raise n to power k modulo m
unsigned long long pow_mod(unsigned n, unsigned k, unsigned m)
{
    unsigned long long acc, prod;
    assert(m > 1);
    
    if (!k)
        return 1;
    
    acc = n % m;
    prod = 1;
    for (; k > 0; )
    {
        if (k % 2)
            prod = (prod * acc) % m;
        acc = (acc * acc) % m;
        k /= 2;
    }

    return prod;
}

int is_equal(const char *l, const char *r, size_t len)
{
    for (int i = 0; i < len; ++i)
        if (l[i] != r[i])
            return 0;

    return 1;
}

// возвращает номер позиции на которой needle расположена внутри haystack
// или -1 если ничего не найдено
int rabin_karp(const char *needle, const char *haystack) 
{
    unsigned n, target, cur, left = 0, right = strlen(needle);
    int res = -1;
    
    target = get_hash(needle, needle + right);
    cur = get_hash(haystack, haystack + right);
    n = pow_mod(R, right - 1, Q);

    // сравниваем до haystack[right] не включая его
    while (haystack[right - 1])
    {        
        if (target == cur)
            if (is_equal(needle, &haystack[left], strlen(needle)))
            {
                res = left;
                break;
            }

        cur = update_hash(cur, n, haystack[left], haystack[right]);
        left += 1;
        right += 1;
    }
    
    return res;
}

int read_input(char **hay)
{
    int ndl_count = 0, res;
    long unsigned lusz, tmp2;
    char temp[16] = {0};

    // количество ответов (и вопросов) 
    res = scanf("%d\n", &ndl_count);
    if (res != 1)
    {
        fprintf(stderr, "Error in input");
        abort();
    }

    // текст для поиска
    res = scanf("%lu\n", &lusz);
    if (res != 1)
    {
        fprintf(stderr, "Error in input");
        abort();
    }

    ++lusz; // завершающий 0
    *hay = calloc(lusz, sizeof(char));
    if (!(*hay))
    {
        fprintf(stderr, "Calloc error");
        abort();
    }

    if (!fgets(*hay, lusz, stdin))
    {
        fprintf(stderr, "Error in input");
        free(*hay);
        abort();
    }
    
    // поисковые запросы
    res = scanf("%lu\n", &lusz);
    if (res != 1)
    {
        fprintf(stderr, "Error in input");
        free(*hay);
        abort();
    }

    return ndl_count;
}

void main()
{
    char *hay = NULL;
    int ndl_size = read_input(&hay);

    for (int i = 0; i < ndl_size; ++i)
    {
        int count = 0, start = 0, found, ndl_len;
        char needle[1024];

        if (1 != scanf("%s", needle))
        {
            fprintf(stderr, "Input error");
            free(hay);
            abort();
        }

        ndl_len = strlen(needle);

        while((found = rabin_karp(needle, &hay[start])) != -1)
        {
            ++count;
            start += (found + ndl_len);
        }

        printf("%d ", count);
    }

    printf("\n");
    free(hay);
}