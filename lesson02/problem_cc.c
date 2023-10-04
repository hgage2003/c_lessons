#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>

struct sieve_t
{
	unsigned long long size;
	unsigned char *sieve;
};

struct sieve_t init_sieve(unsigned long long size)
{
	struct sieve_t res;
	res.sieve = calloc(size, sizeof(unsigned char));
	
	if (!res.sieve)
	{
		printf("Error: out of memory\n");
		abort();
	}

	res.size = size;

	for (unsigned long long i = 2; i * i <= res.size; ++i)
	{
		if (res.sieve[i])
			continue;

		for (unsigned long long j = i * 2; j < res.size; j += i)
			res.sieve[j] = 1;
	}

	return res;
}

void free_sieve(struct sieve_t *s)
{
    assert(s != 0);

	free(s->sieve);
	s->sieve = 0;
	s->size = 0;
}
 
unsigned char is_prime(struct sieve_t s, unsigned n)
{
	assert(n < s.size);
	return(s.sieve[n] == 1) ? 0 : 1;
}

int is_circular_prime(struct sieve_t s, int n)
{
    int rank = 1;

    if (n < 0)
        n = -n;

    for (int i = n / 10; i > 0; i /= 10)
        rank *= 10;
    
    for (int i = 1; i < n; i *= 10)
    {
        int mod = n % 10, quot = n / 10;

        if (!is_prime(s, n))
            return 0;

        n = rank * mod + quot;
    }

    return 1;
}

int bound(int n)
{
    // всегда найдется результат в диапазоне [0, n],
    // значит нужно подготовить решето для 2n циклических проверок
    int max_test = (n < 0) ? -2 * n : 2 * n;

    // на 1 разряд больше, чтобы получить максимум в разряде, вычтя 1
    int res = 10;

    while (res < max_test)
        res *= 10;

    return res - 1;
}

void read_input(int* n)
{
    int ninput = scanf("%d", n);
    if (ninput != 1)
    {
        printf("Error: wrong input\n");
        abort();
    }
}

int main()
{
    int n, result, step = 0;
    struct sieve_t s;

    read_input(&n);

    s = init_sieve(bound(n));

    for (;;++step)
    {
        result = n + step;

        if (is_circular_prime(s, result))
            break;

        if (step == 0)
            continue;

        result = n - step;
        if (is_circular_prime(s, result))
            break;
    }

    free_sieve(&s);

    printf("%d\n", result);
}