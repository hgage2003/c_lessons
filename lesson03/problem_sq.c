#include <assert.h>

void swap(int *arr, unsigned i, unsigned j)
{
    if (i != j)
    {
        int t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
    }
}

unsigned partition(int *arr, unsigned low, unsigned high) 
{
    unsigned key = low++, pos;

    while (low < high)
    {
        if (arr[key] >= arr[low])
        {
            ++low;
            continue;
        }

        if (arr[key] < arr[high]) 
        {
            --high;
            continue;
        }

        assert(arr[low] > arr[high]);
        swap(arr, low, high);
        ++low; --high;
    }

    if (arr[high] > arr[key])
        pos = high - 1;
    else
        pos = high;

    swap(arr, key, pos);

    return pos;
}

#ifdef NDEBUG

#include <stdlib.h>
#include <malloc.h>

void qsort_impl(int *arr, unsigned low, unsigned high) {
  if (low >= high) return;
  unsigned pi = partition(arr, low, high);
  if (pi > low) qsort_impl(arr, low, pi - 1);
  qsort_impl(arr, pi + 1, high);
}

void qsort_my(int *arr, unsigned len) {
  qsort_impl(arr, 0u, len - 1);
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
        qsort_my(arr.data, arr.size);

    for (int i = 0; i < arr.size; ++i)
        printf((i < arr.size - 1) ? "%d " : "%d\n", arr.data[i]);

    free(arr.data);
}

#endif