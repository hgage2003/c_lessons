#include <stdio.h>
#include <malloc.h>

#ifdef NDEBUG
#include <stdlib.h>     // abort
#endif

typedef int (*cmp_t)(const void *lhs, const void *rhs);

void *cbsearch(const void *key, const void *base, int num, int size, cmp_t cmp)
{
    unsigned l = 0, r = num - 1, med = r;
    int cmp_res;
    void* pmed;

    while (l < (r - 1))
    {
        med = (l + r) / 2;
        pmed = (void*)((char*)base + med * size);
        cmp_res = cmp(key, pmed);
        if (!cmp_res)
            return pmed;
        if (cmp_res < 0)
            r = med;
        else
            l = med;
    }

    return NULL;
}

#ifdef NDEBUG
int int_comp(void const * lhs, void const * rhs)
{
    if (*((const int *)lhs) < *((const int *)rhs))
        return -1;
    else if (*((const int *)lhs) > *((const int *)rhs))
        return 1;

    return 0; 
}

struct array_int
{
    int* data;
    unsigned size;
};

struct array_int read_input(int *key)
{
    struct array_int arr;

    if ((scanf("%d", &arr.size) != 1) || (arr.size <= 0))
    {
        printf("Error: wrong input\n");
        abort();
    }

    arr.data = malloc(arr.size * sizeof(int));
    if (arr.data == NULL)
    {
        printf("Error: malloc error\n");
        abort();
    }

    for (int i = 0; i < arr.size; ++i)
        if (scanf("%d", &arr.data[i]) != 1)
        {
            printf("Error: wrong input\n");
            free(arr.data);
            abort();
        }
    
    if ((scanf("%d", key) != 1))
    {
        printf("Error: wrong input\n");
        abort();
    }

    return arr;
}

int main()
{
    struct array_int arr;
    int key;
    int *res;

    arr = read_input(&key);

    res = cbsearch(&key, arr.data, arr.size, sizeof(int), int_comp);

    if (res != NULL)
        printf("%d\n", *(int*)res);
    else
        printf("Key %d is not found\n", key);

    free(arr.data);
}

#endif