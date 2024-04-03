/*
Problem SR — переворот подстрок
Ваша задача написать программу которая переворачивает в некоей строке все вхождения
определённой подстроки

Например для подстроки "world" и строки "Hello, world!" результатом должно быть "Hello, dlrow!"

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

Вход: 5 world 13 Hello, world!

Выход: Hello, dlrow!

Пример 2

Вход: 3 abc 51 qffUt g abcykvabcb x Lv BRabc g KUrabcN wQabcylz R

Выход: qffUt g cbaykvcbab x Lv BRcba g KUrcbaN wQcbaylz R
*/

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void read_input(char** word, char** text)
{
    int sz; char spc;
    int res = scanf("%d", &sz);
    if (res != 1)
    {
        fprintf(stderr, "Error in input");
        abort();
    }

    res = scanf("%c", &spc);
    if (res != 1 || !isspace(spc))
    {
        fprintf(stderr, "Error in input");
        abort();
    }

    *word = calloc(sz + 1, sizeof(char));
    if (!(*word))
    {
        fprintf(stderr, "Calloc error");
        abort();
    }

    for (int i = 0; i < sz; ++i)
    {
        res = scanf("%c", &((*word)[i]));
        if (res != 1)
        {
            fprintf(stderr, "Error in input");
            free(*word);
            abort();
        }
    }

    res = scanf("%d", &sz);
    if (res != 1)
    {
        fprintf(stderr, "Error in input");
        free(*word);
        abort();
    }

    res = scanf("%c", &spc);
    if (res != 1 || !isspace(spc))
    {
        fprintf(stderr, "Error in input");
        abort();
    }
    
    *text = calloc(sz + 1, sizeof(char));
    if (!(*text))
    {
        fprintf(stderr, "Calloc error");
        free(*word);
        abort();
    }

    for (int i = 0; i < sz; ++i)
    {
        res = scanf("%c", &((*text)[i]));
        if (res != 1)
        {
            fprintf(stderr, "Error in input");
            free(*word);
            free(*text);
            abort();
        }
    }
}

int main()
{
    char *word, *text, *found;
    int wlen;
    read_input(&word, &text);

    wlen = strlen(word);
    found = text;

    while (found = strstr(found, word))
    {
        for (int i = 0; i < wlen; ++i)
            found[i] = word[wlen - i - 1];

        found += wlen;
    }   

    printf("%s\n", text);

    free(word);
    free(text);
}