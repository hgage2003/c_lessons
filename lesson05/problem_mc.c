/*
Problem MC — размен монет
Вам необходимо написать программу, которая, считывая со стандартного ввода:

Сумму размена
Число номиналов для размена
Номиналы для размена
Выдавала бы на стандартный вывод минимальное количество монет для размена

Можно использовать сколько угодно монет каждого номинала

Вы можете быть уверены, что общая сумма не слишком велика (не больше 10000) и что размен всегда
возможен


Пример 1:

Вход: 14 3 1 3 4

Означает выяснить размер минимального размена 14 номиналами 1, 3 и 4

Выход: 4

Лучший вариант это 4 + 4 + 3 + 3


Пример 2:

Вход: 575 7 112 136 200 31 298 304 499

Выход: 5

Лучший вариант это 136 + 136 + 136 + 136 + 31
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <malloc.h>

int min(int a, int b)
{
    return (a < b) ? a : b;
}

void read_input(int *sum, int *coins_cnt, int **coins)
{
    int res;

    res = scanf("%d", sum);
    if (res != 1)
    {
        fprintf(stderr, "Wrong input: (sum(!) coins_count coin[0] .. coin[coins_cnt - 1]\n");
        abort();
    }

    res = scanf("%d", coins_cnt);
    if (res != 1)
    {
        fprintf(stderr, "Wrong input: (sum coins_count(!) coin[0] .. coin[coins_cnt - 1]\n");
        abort();
    }

    *coins = calloc(*coins_cnt, sizeof(int));
    if (!(*coins))
    {
        fprintf(stderr, "Error in calloc\n");
        abort();
    }

    for (int i = 0; i < *coins_cnt; ++i)
    {
        res = scanf("%d", &((*coins)[i]));
        if (res != 1)
        {
            fprintf(stderr, "Wrong input: (sum coins_count(!) coin[0] .. coin[%d] .. coin[coins_cnt - 1]\n", i);
            free(*coins);
            abort();
        }
    }
}

int calc_change(int sum, int coins_cnt, const int* coins, int *V)
{
    if (sum == 0)
        return 0;
    
    if (sum < 0)
        return INT_MAX;
    
    if (V[sum] != INT_MAX)
        return V[sum];

    for (int i = 0; i < coins_cnt; ++i)
    {
        int CT = calc_change(sum - coins[i], coins_cnt, coins, V);
        if (CT == INT_MAX)
            continue;

        V[sum] = min(V[sum], CT + 1);
    }

    return V[sum];
}

int main()
{
    int sum, coins_cnt, *coins, *V, res;

    read_input(&sum, &coins_cnt, &coins);
    
    V = malloc((sum + 1) * sizeof(int));
    if (!V)
    {
        fprintf(stderr, "Error in calloc\n");
        free(coins);
        abort();
    }
    
    for (int i = 0; i <= sum; ++i)
        V[i] = INT_MAX;

    res = calc_change(sum, coins_cnt, coins, V);
    printf("%d\n", res);

    free(V);
    free(coins);
}