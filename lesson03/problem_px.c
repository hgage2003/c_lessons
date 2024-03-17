#ifdef NDEBUG
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

const int N = 2;
#endif

unsigned mult_row_col(unsigned (*A)[N], unsigned (*B)[N], unsigned row, unsigned col)
{
    unsigned res = 0;
    for (int i = 0; i < N; ++i)
        res += A[row][i] * B[i][col];
    
    return res;
}

//result copied to martix A
void mulNxN(unsigned (*A)[N], unsigned (*B)[N], unsigned m)
{
    unsigned (*temp)[N] = calloc(N * N, sizeof(unsigned));

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            temp[i][j] = mult_row_col(A, B, i, j) % m;

    memcpy(A, temp, N * N * sizeof(unsigned));
    free(temp);
}

void powNxN (unsigned (*A)[N], unsigned k, unsigned m)
{
    unsigned (*prod)[N], (*mult)[N];
    
    // prod is identity matrix
    prod = calloc(N * N, sizeof(unsigned));
    if (!prod)
    {
        fprintf(stderr, "Error in calloc\n");
        abort();
    }

    for (int i = 0; i < N; ++i)
        prod[i][i] = 1;

    // mult is A
    mult = calloc(N * N, sizeof(unsigned));
    if (!mult)
    {
        fprintf(stderr, "Error in calloc\n");
        free(prod);
        abort();
    }
    memcpy(mult, A, N * N * sizeof(unsigned));

    while (k != 0)
    {
        if ((k % 2) == 1)
        {
            // prod = (prod * mult) mod m
            mulNxN(prod, mult, m);
            k -= 1;
        }

        if (k)
        {
            // mult = (mult * mult) % mod;
            mulNxN(mult, mult, m);
            k /= 2;
        }
    }

    memcpy(A, prod, N * N * sizeof(unsigned));
    free(mult);
    free(prod);
}

#ifdef NDEBUG
void printNxN(unsigned (*A)[N])
{
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            if ((i < N - 1) || (j < N - 1))
                printf("%d ", A[i][j]);
            else
                printf("%d\n", A[i][j]);
        }
}

int main()
{
    unsigned (*res)[N];
    res = calloc(N * N, sizeof(unsigned));

    res[0][0] = res[0][1] = res[1][0] = 1;
     
    powNxN(res, 20, 10);
     
    printNxN(res);
    free(res);
}
#endif