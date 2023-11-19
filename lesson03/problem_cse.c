#ifdef NDEBUG
#include <stdlib.h>     // abort
#endif

#include <stdio.h>
#include <malloc.h>
#include <string.h>     // memcpy

typedef int (*cmp_t)(void const * lhs, void const * rhs);

void swap(void * parr, int eltsize, unsigned i, unsigned j)
{
    if (i != j)
    {
        void *t = malloc(eltsize);
        if (t == NULL)
        {
            printf("Error: malloc error\n");
            return;
        }

        memcpy(t, (char*)parr + i * eltsize, eltsize);
        memcpy((char*)parr + i * eltsize, (char*)parr + j * eltsize, eltsize);
        memcpy((char*)parr + j * eltsize, t, eltsize);
        free(t);
    }
}

int selstep(void * parr, int eltsize, int numelts, int nsorted, cmp_t cmp) 
{
    int minpos = nsorted;
    if (nsorted >= numelts)
        return 1;

    for (int i = minpos; i < numelts; ++i)
        if (cmp((char*)parr + i * eltsize, (char*)parr + minpos * eltsize))
            minpos = i;

    if ((minpos < numelts) && (minpos != nsorted))
        swap(parr, eltsize, nsorted, minpos);

    return 0; 
}

#ifdef NDEBUG

int int_comp(void const * lhs, void const * rhs)
{
    if (*((const int *)lhs) < *((const int *)rhs))
        return 1;

    return 0; 
}

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

    return arr;
}

int main()
{
    struct array_int arr;

    arr = read_input();

    for (int i = 0; i < arr.size; ++i)
        selstep(arr.data, sizeof(int), arr.size, i, int_comp);

    for (int i = 0; i < arr.size; ++i)
        printf((i < arr.size - 1) ? "%d " : "%d\n", arr.data[i]);

    free(arr.data);
}

#endif