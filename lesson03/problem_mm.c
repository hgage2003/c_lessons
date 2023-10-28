#include <stdio.h>
#include <stdlib.h>     // abort()
#include <malloc.h>

int* read_input(int* arrsize)
{
    int *arr = NULL, ninput = scanf("%d", arrsize);

    if ((ninput != 1) || (*arrsize < 0))
    {
        printf("Error: wrong input\n");
        abort();
    }

    if (*arrsize == 0)
        return arr;

    arr = malloc(*arrsize * sizeof(int));
    if (arr == NULL)
    {
        printf("Error: malloc error\n");
        abort();
    }

    for (int i = 0; i < *arrsize; ++i)
    {
        ninput = scanf("%d", &arr[i]);
        if (ninput != 1)
        {
            printf("Error: wrong input\n");
            free(arr);
            abort();
        }
    }

    return arr;
}

int main()
{
    int *arr, arrsize, min, max;

    arr = read_input(&arrsize);
    if (arrsize == 0)
        min = max = 0;
    else
        min = max = arr[0];

    for (int i = 0; i < arrsize; ++i)
    {
        if (arr[i] < min)
            min = arr[i];

        if (arr[i] > max)
            max = arr[i];
    }

    free(arr);
    printf("%d %d\n", min, max);
}