#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>

#define MAX_LEN 100

struct sieve_t
{
	unsigned long long size;
	unsigned char *sieve;
};

struct formula_data
{
    int a;
    int b;
    int len;
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

    if (n <= 1)
        return 0;

	return(s.sieve[n] == 1) ? 0 : 1;
}

unsigned long long bound(int n)
{
    unsigned long long res;
    assert(n > 0);

    res = (unsigned long long)MAX_LEN * MAX_LEN + n * MAX_LEN + n;

    return res;
}

int test_formula(struct sieve_t s, int a, int b)
{
    int num = 0;

    for (;; ++num)
    {
        int res = num * (num + a) + b;
        if (res < 0)
            res = -res;

        if (!is_prime(s, res))
            break;
    }

    return num;
}

void read_input(int* n)
{
    int ninput = scanf("%d", n);
    if ((ninput != 1) || (*n == 0))
    {
        printf("Error: wrong input\n");
        abort();
    }
}

int main()
{
    int n, max_len = 0;
    struct formula_data res = {0};
    struct sieve_t s;

    read_input(&n);

    if (n < 0)
        n = -n;

    s = init_sieve(bound(n));

    for (int a = -n; a < n; ++a)
        for (int b = -n; b < n; ++b)
        {
            int len = test_formula(s, a, b);
            if (len > max_len)
            {
                res.a = a;
                res.b = b;
                max_len = res.len = len;
            }
        }

    free_sieve(&s);

    printf("%d %d %d\n", res.a, res.b, res.len);
}