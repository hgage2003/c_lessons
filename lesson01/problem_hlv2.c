#include <stdio.h>
#include <assert.h>

const int ARRAY_SIZE = 6;

int next_permutation(int*);
int is_solution(int*);
int is_minimal(int*);
void print_res(int*);

int main()
{
    int arr[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; ++i)
        arr[i] = i + 1;

    do
    {
        if (is_solution(arr))
            if (is_minimal(arr))
                print_res(arr);
    }
    while (next_permutation(arr));
}

void swap(int* arr, int i, int j)
{
    int t;
    assert((i < ARRAY_SIZE) && (j < ARRAY_SIZE));
    assert((i >= 0) && (j >= 0));

    t = arr[i]; 
    arr[i] = arr[j];
    arr[j] = t;
}

int next_permutation(int* arr)
{
    int j = ARRAY_SIZE - 2, k = ARRAY_SIZE - 1, l, r;

    while ((j != -1) && (arr[j] >= arr[j + 1]))
        --j;

    if (j == -1)
        return 0;

     while (arr[j] >= arr[k])
        --k;
    
    swap(arr, j, k);

    l = j + 1; r = ARRAY_SIZE - 1;
    while (l < r)
        swap(arr, l++, r--);

    return 1;
}

int is_solution(int* arr)
{
    int sum;
    assert(ARRAY_SIZE == 6);

    sum = arr[0] + arr[1] + arr[5];
    if (sum != (arr[1] + arr[2] + arr[3]))
        return 0;
    if (sum != (arr[2] + arr[0] + arr[4]))
        return 0;

    return 1;
}

int is_minimal(int* arr)
{   
    assert(ARRAY_SIZE == 6);
    if ((arr[3] < arr[5]) && (arr[3] < arr[4]))
        return 1;

    return 0;
}

void print_res(int* arr)
{
    assert(ARRAY_SIZE == 6);
    printf("%d,%d,%d; %d,%d,%d; %d,%d,%d\n",    arr[3], arr[2], arr[1],
                                                arr[5], arr[1], arr[0],
                                                arr[4], arr[0], arr[2]);
}