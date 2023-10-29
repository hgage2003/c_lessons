
;   // needed to compile in contest
#ifdef NDEBUG
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#endif

int moveright(int *arr, int key, int last) 
{
    int pos;
    for (pos = 0; pos < last; ++pos)
        if (arr[pos] > key)
        {
            for (int j = last; j > pos; --j)
                arr[j] = arr[j - 1];
            break;
        }
    return pos;
}

#ifdef NDEBUG
struct array_int
{
    int* data;
    unsigned size;
};

void free_array(struct array_int *arr);
struct array_int* read_input();
void inssort(int *arr, int len);

int main()
{
    struct array_int *arr = read_input();
    
    inssort(arr->data, arr->size);
    
    for (int i = 0; i < arr->size; ++i)
        printf((i < arr->size - 1) ? "%d ": "%d\n", arr->data[i]);

    free_array(arr);
}

void free_array(struct array_int *arr)
{
    if (arr == NULL)
        return;

    free(arr->data);
    free(arr);
    arr = NULL;
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

void inssort(int *arr, int len) 
{
    int i;
    for (i = 0; i < len; ++i) {
        int key, pos;
        key = arr[i];
        pos = moveright(arr, key, i);
        arr[pos] = key;
    }
}
#endif