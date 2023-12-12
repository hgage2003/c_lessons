#include <stdio.h>
#include <stdlib.h>     //abort
struct poly
{
    int size;
    int *coeff;
};

void read_input(struct poly *a, struct poly *b)
{
    int ninput = scanf("%d", &a->size);
    if (ninput != 1)
    {
        printf("Error: wrong input\n");
        abort();
    }

    ninput = scanf("%d", &b->size);
    if (ninput != 1)
    {
        printf("Error: wrong input\n");
        abort();
    }

    a->coeff = calloc(a->size, sizeof(int));
    if (a->coeff == NULL)
    {
        printf("Error in calloc\n");
        abort();
    }

    for (int i = 0; i < a->size; ++i)
    {
        ninput = scanf("%d", &a->coeff[i]);
        if (ninput != 1)
        {
            printf("Error: wrong input\n");
            free(a->coeff);
            abort();
        }
    }

    b->coeff = calloc(b->size, sizeof(int));
    if (b->coeff == NULL)
    {
        printf("Error in calloc\n");
        free(a->coeff);
        abort();
    }

    for (int i = 0; i < b->size; ++i)
    {
        ninput = scanf("%d", &b->coeff[i]);
        if (ninput != 1)
        {
            printf("Error: wrong input\n");
            free(a->coeff);
            free(b->coeff);
            abort();
        }
    }
}

struct poly poly_mult(const struct poly *a, const struct poly *b)
{
    struct poly res;
    res.size = a->size + b->size - 1;
    res.coeff = calloc(res.size, sizeof(int));

    if (res.coeff == NULL)
    {
        printf("Error in calloc\n");
        return res;
    }

    for (int i = 0; i < a->size; ++i)
        for (int j = 0; j < b->size; ++j)
            res.coeff[i + j] += a->coeff[i] * b->coeff[j];

    return res;
}

int main()
{
    struct poly a, b, res;

    read_input(&a, &b);

    res = poly_mult(&a, &b);

    if (res.coeff != NULL)
    {
        int max_pow = 0;
        for (int i = 0; i < res.size; ++i)
            if (res.coeff[i] != 0)
                max_pow = i;

        for (int i = 0; i <= max_pow; ++i)
            printf((i < max_pow) ? "%d " : "%d\n", res.coeff[i]);
    }
    
    free(a.coeff);
    free(b.coeff);
    free(res.coeff);
}