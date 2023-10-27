#include <stdio.h>
#include <stdlib.h>     // abort()
#include <assert.h>
#include <malloc.h>

/*
Магические тройки

Задается N - количество точек внутренней фигуры.
Всего в сетке 2*N ячеек, которые хранятся в одномерном массиве.

Ячейки массива располагаются по сетке следующим образом:
Сначала внешние "хвосты" по часовой стрелке, потом внутренняя фигура.
Треугольная сетка будет иметь тройки ячеек с номерами {1,4,5}, {2,5,6} и {3,6,4}.

Подходящие тройки находятся перебором всех перестановок по порядку 
с проверкой равенства троек.

Функция next_permutation выполняет следующую перестановку по возрастанию
и возвращает 0, если следующая перестановка невозможна.
Из массива [1,2,3,4,5,6] в конце концов придет к [6,5,4,3,2,1] 
*/

int N;

int next_permutation(int*);
int is_solution(int*);
int is_minimal(int*);
void print_res(int*);

void read_input(int *n)
{
    int ninput;
    ninput = scanf("%d", n);
    if ((ninput != 1) || (*n < 3))
    {
        printf("error: wrong input\n");
        abort();
    }
}

int main()
{
    int *array;
    read_input(&N);

    array = malloc(2 * N * sizeof(int));

    for (int i = 0; i < 2 * N; ++i)
        array[i] = i + 1;

    do
    {
        if (is_solution(array))
            if (is_minimal(array))
                print_res(array);
    }
    while (next_permutation(array));

    free(array);
}

void swap(int* arr, int i, int j)
{
    int t;
    assert((i < (2 * N)) && (j < (2 * N)));
    assert((i >= 0) && (j >= 0));

    t = arr[i]; 
    arr[i] = arr[j];
    arr[j] = t;
}

int next_permutation(int* arr)
{
    int j = 2 * N - 2, k = 2 * N - 1, l, r;

    while ((j != -1) && (arr[j] >= arr[j + 1]))
        --j;

    if (j == -1)
        return 0;

     while (arr[j] >= arr[k])
        --k;
    
    swap(arr, j, k);

    l = j + 1; r = 2 * N - 1;
    while (l < r)
        swap(arr, l++, r--);

    return 1;
}

int is_solution(int* arr)
{
    int sum;
    assert(N >= 3);

    sum = arr[N - 1] + arr[2 * N - 1] + arr[N];

    for (int i = 0; i < N - 1; ++i)
        if ((arr[i] + arr[N + i] + arr[N + i + 1]) != sum)
            return 0;

    return 1;
}

int is_minimal(int* arr)
{   
    for (int i = 1; i < N; ++i)
        if (arr[i] < arr[0])
            return 0;

    return 1;
}

void print_res(int* arr)
{
    for (int i = 0; i < N - 1; ++i)
        printf("%d,%d,%d; ", arr[i], arr[N + i], arr[N + i + 1]);

    printf("%d,%d,%d\n", arr[N - 1], arr[2 * N - 1], arr[N]);
}