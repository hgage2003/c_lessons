/*
    Problem RBS — корзинная сортировка
    Сформируем бакеты разделив максимальное число M на N частей.

    На вход вам приходит длина массива и далее сам массив.

    Ваша задача распечатать через пробелы все бакеты. Разделите их нулевыми символами (ноль в конце
    каждого бакета).


    Пример 1

    Вход: 8 126 348 343 432 316 171 556 670

    Выход: 0 126 0 171 0 316 0 343 348 0 432 0 556 0 670 0


    Пример 2

    Вход: 10 187 329 731 517 71 468 429 237 621 860

    Выход: 71 0 0 187 237 0 329 0 429 0 468 0 517 0 621 0 731 0 860 0
*/

#include <stdio.h>
#include <stdlib.h>

struct node_t
{
    struct node_t *next;
    int data;
};

struct array_int
{
    int* data;
    unsigned size;
};

struct array_int read_input()
{
    struct array_int arr;

    if ((scanf("%d", &arr.size) != 1) || (arr.size <= 0))
    {
        fprintf(stderr, "Error: wrong input\n");
        abort();
    }

    arr.data = malloc(arr.size * sizeof(int));
    if (arr.data == NULL)
    {
        fprintf(stderr, "Error: malloc error\n");
        abort();
    }

    for (unsigned i = 0; i < arr.size; ++i)
        if (scanf("%d", &arr.data[i]) != 1)
        {
            fprintf(stderr, "Error: wrong input\n");
            free(arr.data);
            abort();
        }

    return arr;
}

void print_buckets(struct node_t **buckets, unsigned buckets_count)
{
    struct node_t *node;
    for (unsigned i = 0; i < buckets_count; ++i)
    {
        node = buckets[i];
        while (node)
        {
            printf("%d ", node->data);
            node = node->next;
        }

        printf((i == buckets_count - 1) ? "0\n" : "0 ");
    }
}

void free_buckets(struct node_t **buckets, unsigned buckets_count)
{
    for (unsigned i = 0; i < buckets_count; ++i)
    {
        struct node_t* top = buckets[i];
        while (top != NULL)
        {
            struct node_t* temp = top->next;
            free(top);
            top = temp;
        }
    }
    free(buckets);
}

void put_to_bucket(struct node_t **buckets, int num, unsigned bucket_num)
{
    struct node_t *node, *iter;
    
    node = calloc(1, sizeof(struct node_t));
    if (node == NULL)
    {
        fprintf(stderr, "Calloc error\n");
        free_buckets(buckets, bucket_num);
        abort();
    }
    node->data = num;

    iter = buckets[bucket_num];

    // первый граничный случай - новый нод в начале
    if (!iter || iter->data >= node->data)
    {
        node->next = iter;
        buckets[bucket_num] = node;
        return;
    }

    while (iter->next)
    {
        if (iter->next && (iter->next->data >= node->data))
        {
            node->next = iter->next;
            iter->next = node;
            return;
        }

        iter = iter->next;
    }

    // второй граничный случай - наш нод последний
    iter->next = node;
}

int main()
{
    struct array_int in_array;
    unsigned max_int = 0, bucket_size, buckets_count;
    struct node_t **buckets;

    in_array = read_input();

    for (unsigned i = 0; i < in_array.size; ++i)
        if (in_array.data[i] > max_int)
            max_int = in_array.data[i];

    buckets = calloc(in_array.size, sizeof(struct node_t*));
    if (buckets == NULL)
    {
        fprintf(stderr, "Error: malloc error\n");
        free(in_array.data);
        abort();
    }

    buckets_count = in_array.size;
    bucket_size = max_int / buckets_count;

    for (unsigned i = 0; i < in_array.size; ++i)
    {
        unsigned bucket_num = in_array.data[i] / bucket_size;
        
        if (bucket_num >= buckets_count)
            bucket_num = buckets_count - 1;

        put_to_bucket(buckets, in_array.data[i], bucket_num);
    }

    free(in_array.data);

    print_buckets(buckets, buckets_count);
    free_buckets(buckets, buckets_count);
}