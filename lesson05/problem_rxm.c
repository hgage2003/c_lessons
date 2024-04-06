/*
Problem RXM — переворот подстрок с поиском регекспом
Ваша задача написать программу которая переворачивает в некоей строке все вхождения
определённой подстроки

Например для подстроки задаваемой регулярным выражением "wo.*d" и строки "Hello, world!"
результатом должно быть "Hello, dlrow!"

Вы можете предполагать что текст состоит из слов, разделённых пробелами и пунктуацией, а слово
состоит из алфавитных символов

Вы также можете использовать любые функции стандартной библиотеки, включая strstr для поиска
подстроки

Во входных данных идёт сначала длина искомой подстроки, далее отделённая любым одним
пробельным символом сама подстрока, далее длина текста и далее, опять отделённый одним любым
пробельным символом сам текст, в котором нужно сделать поиск и замену

На выходе должен быть распечатан текст с перевёрнутыми подстроками, либо исходный текст, если ни
одной подстроки не найдено

Посылка должна состоять из программы, которая считывает данные со стандартного ввода и печатает
ответ на стандартный вывод


Пример 1

Вход: 5 wo.*d 13 Hello, world!

Выход: Hello, dlrow!

Пример 2

Вход: 12 [ab][ab][bc] 51 qffUt g abcykvabcb x Lv BRabc g KUrabcN wQabcylz R

Выход: qffUt g cbaykvcbab x Lv BRcba g KUrcbaN wQcbaylz R
*/

#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <ctype.h>
#include <malloc.h>
#include <string.h>

void swap(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

void reverse(char *str, unsigned start, unsigned len)
{
    unsigned end = start + len - 1;

    while (start < end)
    {
        swap(&str[start], &str[end]);
        ++start;
        --end;
    }
}

int read_string(char **str, int len)
{
    int res;

    *str = calloc(len + 1, sizeof(char));
    if (!(*str))
    {
        fprintf(stderr, "Error in calloc\n");
        return 1;
    } 

    for (int i = 0; i < len; ++i)
    {
        res = scanf("%c", &((*str)[i]));
        
        if ((*str)[i] == '\n')
            (*str)[i] = 0;

        if (res != 1)
        {
            fprintf(stderr, "Error in input\n");
            free(*str);
            return 1;
        }
    }

    return 0;
}

void read_input(char **regex, char **str)
{
    int res, size;
    char spc;   // пробельный символ между полями ввода

    res = scanf("%d", &size);
    if (res != 1)
    {
        fprintf(stderr, "Error in input\n");
        abort();
    }

    res = scanf("%c", &spc);
    if ((res != 1) || !isspace(spc))
    {
        fprintf(stderr, "Error in input\n");
        abort();
    }

    res = read_string(regex, size);
    if (res)
        abort();

    res = scanf("%d", &size);
    if (res != 1)
    {
        fprintf(stderr, "Error in input\n");
        free(*regex);
        abort();
    }

    res = scanf("%c", &spc);
    if ((res != 1) || !isspace(spc))
    {
        fprintf(stderr, "Error in input\n");
        free(*regex);
        abort();
    }
    
    res = read_string(str, size);
    if (res)
    {
        free(*regex);
        abort();
    }
}

#define MAX_MATCHES 10

int main()
{
    char *regstr, *str;
    regex_t regex;
    char BUFFER[128];
    int res, from = 0;
    regmatch_t matches[MAX_MATCHES];

    read_input(&regstr, &str);

    res = regcomp(&regex, regstr, REG_EXTENDED);
    if (res) 
    {
        regerror(res, &regex, BUFFER, sizeof(BUFFER));
        fprintf(stderr, "Regex match failed: %s\n", BUFFER);

        free(regstr);
        free(str);
        abort();
    }
    free(regstr);

    while (!(res = regexec(&regex, &str[from], MAX_MATCHES, matches, 0))) 
    {
        for (size_t i = 0; i <= regex.re_nsub; ++i)
        {
#if 0
            char buff[20] = "";
            printf("szso[%zu]=%d\n", i, matches[i].rm_so);
            printf("szeo[%zu]=%d\n", i, matches[i].rm_eo);
            memcpy(buff, &str[from] + matches[i].rm_so, matches[i].rm_eo - matches[i].rm_so);
            printf("group[%zu]: [%s]\n", i, buff);
#endif
            reverse(&str[from], matches[i].rm_so, matches[i].rm_eo - matches[i].rm_so);
            from += matches[i].rm_eo;
        }
    }

    printf("%s\n", str);

    regfree(&regex);
    free(str);
}

/*
test 2
6
[ab]*c
8
CVaabc f
->
CVcbaa f
(ans)
CVacba f

test 7
13
await [for]+
13
uoawait forrg
->
uorrof tiawag
(ans)
uorof tiawarg

test 8
14
[xy] [xy] [yz]
12
BVQ x x y zy
->
BVQ y x x zy
(ans)
BVQ x z y xy
*/