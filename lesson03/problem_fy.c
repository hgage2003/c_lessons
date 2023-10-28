#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct array_int
{
    int* data;
    unsigned size;
};

void swap(struct array_int* arr, unsigned i, unsigned j)
{
    int t;
    assert(arr != NULL);

    if ((i < arr->size) && (j < arr->size) && (i != j))
    {
        t = arr->data[i];
        arr->data[i] = arr->data[j];
        arr->data[j] = t;
    }
}

struct array_int* read_input()
{
    struct array_int *res;
    int ninput;
    
    res = calloc(1, sizeof(struct  array_int));
    
    ninput = scanf("%u", &res->size);

    if (ninput != 1)
    {
        printf("Error: wrong input\n");
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

int myrand() 
{
    static unsigned long int seed = 1;
    seed = seed * 1103515245 + 12345;
    return (unsigned int)(seed / 65536) % 32768;
}

int main()
{
    struct array_int* arr;
    
    arr = read_input();

    if (arr->size == 0)
        printf("0\n");
    else
    {
        for (int i = arr->size - 1; i > 0; --i)
        {
            int pos = myrand() % (i + 1);
            swap(arr, pos, i);
        }

        for (int i = 0; i < arr->size; ++i)
            printf((i < arr->size - 1) ? "%d " : "%d\n", arr->data[i]);
    }

    free(arr->data);
    free(arr);
}