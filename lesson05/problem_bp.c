/*
Problem BP — упаковка рюкзака
Вам необходимо написать программу, которая, считывая со стандартного ввода:

Количество вещей
Вес каждой вещи
Общий вес входящий в рюкзак
Подсчитает наибольшее количество вещей которые можно положить в рюкзак


Пример 1

Вход: 10 4 3 1 3 4

Означает: рюкзак, вместимостью 10, и 4 вещи весом 1, 3, 3 и 4

Легко видеть, что больше трёх вещей в этом примере уложить нельзя

Выход: 3


Пример 2

Вход: 15 4 3 1 3 4

Означает: рюкзак, вместимостью 15, то есть с запасом и те же вещи

Легко видеть, что теперь можно уложить все 4

Выход: 4


Пример 3

Вход: 2478 9 112 196 956 1106 1515 1794 1 1799 79

Выход: 6
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <malloc.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void read_input(int *cap, int *item_cnt, int **items)
{
    int res;

    res = scanf("%d", cap);
    if (res != 1)
    {
        fprintf(stderr, "Wrong input: (capacity(!) items_count item[0] .. item[items_cnt - 1]\n");
        abort();
    }

    res = scanf("%d", item_cnt);
    if (res != 1)
    {
        fprintf(stderr, "Wrong input: (capacity items_count(!) item[0] .. item[items_cnt - 1]\n");
        abort();
    }

    *items = calloc(*item_cnt, sizeof(int));
    if (!(*items))
    {
        fprintf(stderr, "Error in calloc\n");
        abort();
    }

    for (int i = 0; i < *item_cnt; ++i)
    {
        res = scanf("%d", &((*items)[i]));
        if (res != 1)
        {
            fprintf(stderr, "Wrong input: (capacity items_count item[0] .. item[%d](!) .. item[items_cnt - 1]\n", i);
            free(*items);
            abort();
        }
    }
}

int calc_items(int w, int i, const int* items, int **V)
{
    int c1, c2;
    if (w < 0 || i < 0)
        return INT_MIN;

    if (w == 0 || i == 0)
        return 0;

    if (V[i][w] != INT_MIN)
        return V[i][w];

    c1 = calc_items(w, i - 1, items, V);
    c2 = calc_items(w - items[i - 1], i - 1, items, V) + 1;
    
    V[i][w] = max(c1, c2);
    
    return V[i][w];
}

int main()
{
    int cap, item_cnt, *items, **V, res;

    read_input(&cap, &item_cnt, &items);

    V = calloc(item_cnt + 1, sizeof(int*));
    if (!V)
    {
        fprintf(stderr, "Error in calloc\n");
        free(items);
        abort();
    }

    for (int i = 0; i <= item_cnt; ++i)
    {
        V[i] = calloc(cap + 1, sizeof(int));
        if (!V[i])
        {
            fprintf(stderr, "Error in calloc\n");
            for (int j = i - 1; j >= 0; --j)
                free(V[j]);   
            free(V);
            free(items);
            abort();
        }

        for (int j = 1; j <= cap; ++j)
            V[i][j] = INT_MIN;
    }

    res = calc_items(cap, item_cnt, items, V);
    printf("%d\n", res);

    for (int i = 0; i <= item_cnt; ++i)
        free(V[i]);
    free(V);

    free(items);
}