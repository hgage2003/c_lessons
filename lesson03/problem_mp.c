#include <stdio.h>
#include <stdlib.h>     //abort
struct poly
{
    int size;
    int *coefficients;
};

void read_input(struct poly *f, struct poly *s)
{
    int ninput = scanf("%d", &f->size);
    if (ninput != 1)
    {
        printf("Error: wrong input\n");
        abort();
    }

    ninput = scanf("%d", &s->size);
    if (ninput != 1)
    {
        printf("Error: wrong input\n");
        abort();
    }

    f->coefficients = calloc(f->size, sizeof(int));
    if (f->coefficients == NULL)
    {
        printf("Error in calloc\n");
        abort();
    }

    for (int i = 0; i < f->size; ++i)
    {
        ninput = scanf("%d", &f->coefficients[i]);
        if (ninput != 1)
        {
            printf("Error: wrong input\n");
            free(f->coefficients);
            abort();
        }
    }

    s->coefficients = calloc(s->size, sizeof(int));
    if (s->coefficients == NULL)
    {
        printf("Error in calloc\n");
        free(f->coefficients);
        abort();
    }

    for (int i = 0; i < s->size; ++i)
    {
        ninput = scanf("%d", &s->coefficients[i]);
        if (ninput != 1)
        {
            printf("Error: wrong input\n");
            free(f->coefficients);
            free(s->coefficients);
            abort();
        }
    }
}

struct poly poly_mult(const struct poly *f, const struct poly *s)
{
    struct poly res;
    res.size = f->size + s->size - 1;
    res.coefficients = calloc(res.size, sizeof(int));

    if (res.coefficients == NULL)
    {
        printf("Error in calloc\n");
        return res;
    }

    for (int i = 0; i < f->size; ++i)
        for (int j = 0; j < s->size; ++j)
            res.coefficients[i + j] += f->coefficients[i] * s->coefficients[j];

    return res;
}

int main()
{
    struct poly first, second, res;

    read_input(&first, &second);

    res = poly_mult(&first, &second);

    if (res.coefficients != NULL)
    {
        int max_pow = 0;
        for (int i = 0; i < res.size; ++i)
            if (res.coefficients[i] != 0)
                max_pow = i;

        for (int i = 0; i <= max_pow; ++i)
            printf((i < max_pow) ? "%d " : "%d\n", res.coefficients[i]);
    }
    
    free(first.coefficients);
    free(second.coefficients);
    free(res.coefficients);
}