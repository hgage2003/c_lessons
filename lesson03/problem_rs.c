#include <stdlib.h>     // abort
#include <stdio.h>
#include <malloc.h>

struct array_int
{
    int* data;
    unsigned size;
};

struct array_int read_input(int *digit)
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

    if (scanf("%d", digit) != 1)
    {
        printf("Error: wrong input\n");
        free(arr.data);
        abort();
    }

    return arr;
}

int get_digit(int value, int pos)
{
    int expn = 1;
    
    while (pos-- > 0)
        expn *= 10;

    return (value / expn) % 10;
}

void radix_sort(struct array_int arr, int digit)
{
    int b[10] = {0};
    int sum = 0, d, temp;
    int *temp_arr;
    
    // fill 10 buckets
    for (int i = 0; i < arr.size; ++i)
    {
        d = get_digit(arr.data[i], digit);
        ++b[d];
    }

    // change counters in buckets to start positions
    for (int i = 0; i < 10; ++i)
    {
        temp = b[i]; 
        b[i] = sum; 
        sum += temp;
    }

    temp_arr = calloc(arr.size, sizeof(int));
    if (temp_arr == NULL)
    {
        printf("Error in calloc\n");
        free(arr.data);
        abort();
    }

    for (int i = 0; i < arr.size; ++i)
    {
        d = get_digit(arr.data[i], digit);
        temp_arr[b[d]] = arr.data[i];
        ++b[d];
    }

    for (int i = 0; i < arr.size; ++i)
        arr.data[i] = temp_arr[i];
    
    free(temp_arr);
}

int main()
{
    struct array_int arr;
    int digit;

    arr = read_input(&digit);

    radix_sort(arr, digit);

    for (int i = 0; i < arr.size; ++i)
        printf((i < arr.size - 1) ? "%d " : "%d\n", arr.data[i]);

    free(arr.data);

}