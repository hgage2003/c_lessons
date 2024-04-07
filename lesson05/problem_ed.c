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
#include <limits.h>
#include <string.h>

int read_string(char **str)
{
    int res, size;

    res = scanf("%d", &size);
    if (res != 1)
        return 1;

    *str = calloc(size + 1, sizeof(char));
    if (!(*str))
    {
        fprintf(stderr, "Error in calloc\n");
        return 1;
    }

    res = scanf("%s", *str);
    if (res != 1)
    {
        free(*str);
        return 1;
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

int calc_cost(int fi, int ti, int costs[3], const char *from, const char *to, int **V)
{
    int add, del, change;

    if ((fi < 0) || (ti < 0))
        return INT_MAX;

    if (fi == 0)
    {
        V[fi][ti] = ti * costs[0]; // добавить ti раз по букве 
        return V[fi][ti];
    }
    if (ti == 0)
    {
        V[fi][ti] = fi * costs[1]; // удалить fi раз по букве
        return V[fi][ti];
    }

    if (V[fi][ti] != INT_MAX)
        return V[fi][ti];
   
    add = calc_cost(fi - 1, ti, costs, from, to, V) + costs[0];
    del = calc_cost(fi, ti - 1, costs, from, to, V) + costs[1];
    change = calc_cost(fi - 1, ti - 1, costs, from, to, V);
    
    if (from[fi - 1] != to[ti - 1])
        change += costs[2];

    V[fi][ti] = min(add, del, change);

    return V[fi][ti];
}

int main()
{
    char *from, *to;
    int costs[3], res, **V;

    read_input(costs, &from, &to);

    V = calloc(strlen(from) + 1, sizeof(char*));
    if (!V)
    {
        fprintf(stderr, "Error in calloc\n");
        free(from);
        free(to);
        return 1;
    }

    for (int i = 0; i <= strlen(from); ++i)
    {
        V[i] = calloc(strlen(to) + 1, sizeof(int));
        if (!V[i])
        {
            fprintf(stderr, "Error in calloc\n");
            
            for (int j = i - 1; j >= 0; --j)
                free(V[j]);
            
            free(V);
            free(from);
            free(to);
            return 1;
        }

        for (int j = 1; j <= strlen(to); ++j)
            V[i][j] = INT_MAX;
    }

    res = calc_cost(strlen(from), strlen(to), costs, from, to, V);
    printf("%d\n", res);

    for (int i = 0; i <= strlen(from); ++i)
    {
#if 0
        for (int j = 0; j <= strlen(to); ++j)
            printf("%d\t", V[i][j]);
        printf("\n");
#endif
        free(V[i]);
    }
    free(V);

    free(from);
    free(to);
}