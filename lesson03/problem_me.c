#ifdef NDEBUG
#include <stdlib.h>     // abort
#endif

#include <stdio.h>
#include <malloc.h>

int majority_element(const int *parr, int len)
{
    int m = -1, count = 0;
    // Find candidate
    for (int i = 0; i < len; ++i)
    {
        if (parr[i] == m)
            ++count;
        else if (count > 0)
            --count;
        else
        {
            m = parr[i];
            count = 1;
        }
    }

    // Check if candidate count > N/2
    count = 0;
    for (int i = 0; i < len; ++i)
        if (parr[i] == m)
            ++count;

    return (count > (len / 2) ? m : -1);
}

#ifdef NDEBUG

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

    printf("%d\n", majority_element(arr.data, arr.size));

    free(arr.data);
}

#endif