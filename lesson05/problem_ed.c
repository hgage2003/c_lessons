/*
Problem ED — расстояние редактирования
Вам необходимо написать программу, которая, считывая со стандартного ввода:

стоимость добавления
стоимость удаления
стоимость замены
длину первой строки
первую строку
длину второй строки
вторую строку
Выводит на стандартный вывод минимальное расстояние редактирования


Пример 1

Вход: 1 1 2 5 spoon 6 sponge

Выход: 3

Пояснение к этому примеру см. на слайдах к семинару
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int read_string(char **str)
{
    int res, size;
    char spc;

    res = scanf("%d", &size);
    if (res != 1)
        return 1;

    *str = calloc(size + 1, sizeof(char));
    if (!(*str))
    {
        fprintf(stderr, "Error in calloc\n");
        return 1;
    }

    res = scanf("%c", &spc);
    if (res != 1 || !isspace(spc))
    {
        fprintf(stderr, "Error in input\n");
        free(*str);
        return 1;
    }

    for (int i = 0; i < size; ++i)
    {
        res = scanf("%c", &((*str)[i]));
        if (res != 1)
        {
            free(*str);
            return 1;
        }
    }

    return 0;
}

void read_input(int costs[3], char **from, char **to)
{
    int res;

    res = scanf("%d %d %d", &costs[0], &costs[1], &costs[2]);
    if (res != 3)
    {
        fprintf(stderr, "Error in input\n");
        abort();
    }

    if (read_string(from))
    {
        fprintf(stderr, "Error in input\n");
        abort();
    }

    if (read_string(to))
    {
        free(*from);
        fprintf(stderr, "Error in input\n");
        abort();
    }
}

int min(int a, int b, int c)
{
    int res = a < b ? a : b;
    return res < c ? res : c;
}

int alloc_matrix(int ***M, int h, int w)
{
    *M = calloc(h, sizeof(int*));
    if (!(*M))
    {
        fprintf(stderr, "Error in calloc\n");
        return 1;
    }

    for (int i = 0; i < h; ++i)
    {
        (*M)[i] = calloc(w, sizeof(int));
        if (!(*M)[i])
        {
            fprintf(stderr, "Error in calloc\n");
            
            for (int j = i - 1; j >= 0; --j)
                free((*M)[j]);
            
            free(*M);
            return 1;
        }
    }

    return 0;
}

void free_matrix(int **M, int h)
{
    for (int i = 0; i < h; ++i)
        free(M[i]);

    free(M);
}

void fill_matrix(int costs[3], const char *from, const char *to, int **V)
{
    int add, del, change;
    for (int i = 0; i <= strlen(from); ++i)
        for (int j = 0; j <= strlen(to); ++j)
        {
            if (!i)
            {
                V[i][j] = j * costs[0];
                continue;
            }
            if (!j)
            {
                V[i][j] = i * costs[1];
                continue;
            }

            add = V[i][j - 1] + costs[0];
            del = V[i - 1][j] + costs[1];
            change = V[i - 1][j - 1];
            
            if (from[i - 1] != to[j - 1])
                change += costs[2];

            V[i][j] = min(add, del, change);
        }
}

int main()
{
    int costs[3], res, **V;
    char *from, *to;
    int flen, tlen;

    read_input(costs, &from, &to);
    flen = strlen(from);
    tlen = strlen(to);

    if (alloc_matrix(&V, flen + 1, tlen + 1))
    {
        fprintf(stderr, "Error in calloc\n");
        free(from);
        free(to);
        abort();
    }

    fill_matrix(costs, from, to, V);
    res = V[flen][tlen];
    printf("%d\n", res);

#if 0
    printf("--------------------------------------------------\n");
    for (int i = 0; i <= flen; ++i)
    {
        for (int j = 0; j <= tlen; ++j)
            printf("%d\t", V[i][j]);
        printf("\n");
    }
    printf("--------------------------------------------------\n");
#endif

    free_matrix(V, flen + 1);
    free(from);
    free(to);
}