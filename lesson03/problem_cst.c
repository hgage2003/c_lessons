#include <stdlib.h>     // abort
#include <stdio.h>
#include <malloc.h>

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

struct array_int fill_buckets(struct array_int array)
{
    struct array_int bckt;
    bckt.size = 0;

    for (int i = 0; i < array.size; ++i)
        if (bckt.size <= array.data[i])
            bckt.size = array.data[i] + 1; // for 0
    
    // alloc and initialize buckets with 0
    bckt.data = calloc(bckt.size, sizeof(int));
    for (int i = 0; i < array.size; ++i)
        ++bckt.data[array.data[i]];

    return bckt; 
}

int main()
{
    struct array_int arr, buckets;

    arr = read_input();

    buckets = fill_buckets(arr);
    
    free(arr.data);

    for (int i = 0; i < buckets.size; ++i)
        printf((i < buckets.size - 1) ? "%d " : "%d\n", buckets.data[i]);

    free(buckets.data);
}