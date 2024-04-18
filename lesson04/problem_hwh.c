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

#define Q 4096 // мощность
#define P 4099 // P - простое число, большее Q
#define A 99   // коэффициент

struct dictnode
{
    char *word;
    int count;      // количество повторов в тексте
    struct dictnode* next;
};

// подсчитать хеш строки
int hash(const char *str)
{
    unsigned hash = 0, l = strlen(str);

    for (unsigned i = 0; i < l; ++i)
        hash = ((hash * A) + str[i]) % P;
    
    return hash % Q;
}

int dict_find(struct dictnode *dict[Q], const char* word)
{
    int h = hash(word);
    struct dictnode *it;

    if (!(it = dict[h]))
        return 0;

    while (it)
    {
        if (!strcmp(it->word, word))
            return it->count;

        it = it->next;
    }

    return 0;
}

// копирует строку в словарь
int dict_add(struct dictnode *dict[Q], const char* word)
{
    int h = hash(word), l = strlen(word);
    struct dictnode *it, *node;

    if (!l)
        return 0;

    // ищем слово в словаре
    if ((it = dict[h]))
        for( ; ; )
        {
            if (!strcmp(it->word, word))
            {
                ++it->count;
                return 0;
            }
            if (it->next)
                it = it->next;
            else
                break;
        }
    // слова нет, it показывает, после какого нода его нужно вставить

    node = calloc(1, sizeof(struct dictnode));
    if (!node)
    {
        fprintf(stderr, "Error in calloc\n");
        return 1;
    }
    
    node->count = 1;
    node->word = calloc(l + 1, sizeof(char));
    if (!node->word)
    {
        free(node);
        fprintf(stderr, "Error in calloc\n");
        return 1;
    }
    strcpy(node->word, word);

    if (!it)
    {
        dict[h] = node;
        return 0;
    }

    it->next = node;
    return 0;
}

void dict_free(struct dictnode **dict)
{
    struct dictnode *del;
    for (int i = 0; i < Q; ++i)
    {
        del = dict[i];
        while (del)
        {
            struct dictnode *tmp = del->next;
            free(del->word);
            free(del);
            del = tmp;
        }
    }

    free(dict);
}

int read_dict(struct dictnode **dict)
{
    int res, wordsz = 0, ndl_count;
    long unsigned srtsz;
    char word[100] = {0};
    
    // количество ответов (и вопросов) 
    res = scanf("%d\n", &ndl_count);
    if (res != 1)
    {
        fprintf(stderr, "Error in input");
        abort();
    }

    // словарь
    res = scanf("%lu\n", &srtsz);
    if (res != 1)
    {
        fprintf(stderr, "Error in input");
        abort();
    }

    for (unsigned long i = 0; i < srtsz; ++i)
    {
        char ch;

        res = scanf("%c", &ch);
        if (res != 1)
        {
            fprintf(stderr, "Error in input");
            abort();
        }

        if (ch ==' ')
        {
            word[wordsz] = 0;
            wordsz = 0;
            dict_add(dict, word);
        }
        else
            word[wordsz++] = ch;
    }
    word[wordsz] = 0;
    dict_add(dict, word);

    return ndl_count;
}

int main()
{
    struct dictnode** dict;
    int ans_cnt, ans_sz, res;

    dict = calloc(Q, sizeof(struct dictnode*));
    if (!dict)
    {
        fprintf(stderr, "Error in calloc\n");
        abort();
    }
    
    ans_cnt = read_dict(dict);

    // поисковые запросы
    res = scanf("%d\n", &ans_sz);
    if (res != 1)
    {
        fprintf(stderr, "Error in input");
        dict_free(dict);
        abort();
    }

    for (int i = 0; i < ans_cnt; ++i)
    {
        char word[100];
        int cnt;

        res = scanf("%s", word);
        if (res != 1)
        {
            fprintf(stderr, "Error in input");
            dict_free(dict);
            abort();
        }

        cnt = dict_find(dict, word);
        printf("%d ", cnt);
    }

    printf("\n");
    dict_free(dict);
}