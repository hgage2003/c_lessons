#include <stdio.h>
#include <stdlib.h>     // abort()
#include <malloc.h>

struct array_int
{
    int* data;
    unsigned size;
};

struct array_int* read_input()
{
    struct array_int *res;
    int ninput;
    
    res = calloc(1, sizeof(struct  array_int));
    
    ninput = scanf("%u", &res->size);

    if (ninput != 1)
    {
        printf("Error: wrong input\n");
        free(res);
        abort();
    }

    if (res->size == 0)
    {
        res->data = NULL;
        return res;
    }

    res->data = malloc(res->size * sizeof(int));
    if (res->data == NULL)
    {
        printf("Error: malloc error\n");
        free(res);
        abort();
    }

    for (int i = 0; i < res->size; ++i)
    {
        ninput = scanf("%d", &res->data[i]);
        if (ninput != 1)
        {
            printf("Error: wrong input\n");
            free(res->data);
            free(res);
            abort();
        }
    }

    return res;
}

int main()
{
    struct array_int *arr = NULL;
    int min, max;

    arr = read_input();
    if (arr->size == 0)
        min = max = 0;
    else
        min = max = arr->data[0];

    for (int i = 0; i < arr->size; ++i)
    {
        if (arr->data[i] < min)
            min = arr->data[i];

        if (arr->data[i] > max)
            max = arr->data[i];
    }

    free(arr->data);
    free(arr);
    printf("%d %d\n", min, max);
}