
#ifdef NDEBUG

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

void merge(int *arr, int l, int m, int r);

void merge_sort_imp(int *arr, int l, int r) {
  if (l >= r) return;
  int m = (l + r) / 2;
  merge_sort_imp(arr, l, m);
  merge_sort_imp(arr, m + 1, r);
  merge(arr, l, m, r);
}

void merge_sort(int *arr, int n) {
  merge_sort_imp(arr, 0, n - 1);
}

int main()
{
    int arr[] = {10, 4, 5, 6, 9, 2, 7, 1, 3, 8};
    int arr_size = sizeof(arr) / sizeof(int);

    for (int i = 0; i < arr_size; ++i)
        printf( (i < arr_size - 1) ? "%d " : "%d\n", arr[i]);

    merge_sort(arr, arr_size);

    for (int i = 0; i < arr_size; ++i)
        printf( (i < arr_size - 1) ? "%d " : "%d\n", arr[i]);
}
#endif

void merge(int *arr, int l, int m, int r)
{
    int temp_sz = r - l + 1, il = l, ir = m + 1;
    int *temp_arr = malloc(temp_sz * sizeof(int));

    if (temp_arr == NULL)
    {
        printf("Error in malloc\n");
        abort();
    }

    for (int i = 0; i < temp_sz; ++i)
        if ((il <= m) && (arr[il] <= arr[ir]) || (ir > r))
            temp_arr[i] = arr[il++];
        else
            temp_arr[i] = arr[ir++];

    for (int i = 0; i < temp_sz; ++i)
        arr[l + i] = temp_arr[i];

    free(temp_arr);
}