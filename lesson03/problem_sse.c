#include <stdio.h>
#include <stdlib.h>     // abort()

struct array_int
{
    int* data;
    unsigned size;
};

struct array_int read_input(int* pos)
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

    if ((scanf("%d", pos) != 1) || (*pos < 0) || (*pos >= arr.size))
    {
        printf("Error: wrong input\n");
        abort();
    }

    return arr;
}

void swap(struct array_int *arr, unsigned i, unsigned j)
{
    if ((i < arr->size) && (j < arr->size) && (i != j))
    {
        int t = arr->data[i];
        arr->data[i] = arr->data[j];
        arr->data[j] = t;
    }
}

unsigned pos_min(const struct array_int *arr, unsigned start)
{
    int minpos = arr->size;
    if (start >= arr->size)
        return minpos;

    minpos = start;
    for (int j = start + 1; j < arr->size; ++j)
        if (arr->data[j] < arr->data[minpos])
            minpos = j;
    
    return minpos;
}

int main()
{
    struct array_int arr;
    int pos, minpos;

    arr = read_input(&pos);

    minpos = pos_min(&arr, pos);
    if ((minpos < arr.size) && (minpos != pos))
        swap(&arr, pos, minpos); 

    for (int i = 0; i < arr.size; ++i)
        printf((i < arr.size - 1) ? "%d " : "%d\n", arr.data[i]);

    free(arr.data);
}