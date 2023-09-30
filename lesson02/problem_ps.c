#define TEST 1

#include <stdio.h>
#include <assert.h>

#if TEST
	#include <math.h>
	#include <malloc.h>
	#include <stdlib.h>

struct sieve_t {
  int n;
  char *s;
};
#endif

unsigned char is_prime(struct sieve_t s, unsigned n)
{
	assert(n < s.n);
	return(s.s[n] == 1) ? 0 : 1;
}

void fill_sieve(struct sieve_t *sv)
{
	for (unsigned long long i = 2; i * i <= sv->n; ++i)
	{
		if (sv->s[i])
			continue;

		for (unsigned long long j = i * 2; j < sv->n; j += i)
			sv->s[j] = 1;
	}
}

int nth_prime(struct sieve_t *sv, int N)
{
	int res = 2;

	assert(N > 0);

	while (--N)
		while(!is_prime(*sv, ++res))
			;

	return res;
}

#if TEST
struct sieve_t init_sieve(unsigned long long size)
{
	struct sieve_t res;
	res.s = calloc(size, sizeof(unsigned char));
	
	if (!res.s)
	{
		printf("Error: out of memory\n");
		abort();
	}

	res.n = size;

	fill_sieve(&res);

	return res;
}

void free_sieve(struct sieve_t *s)
{
	free(s->s);
	s->s = 0;
	s->n = 0;
}

unsigned long long sieve_bound(unsigned num)
{
	assert(num > 20);
	double dnum = num;
	double dres = dnum * (log(dnum) + log(log(dnum)));
	return (unsigned long long) round(dres);
}

void read_input(unsigned *n)
{
	int ninput = scanf("%ud", n);
	if (ninput != 1 || (*n < 1))
	{
		printf("Error: wrong input\n");
		abort();
	}
}

int main()
{
	unsigned num;
	unsigned long long bound, res = 0;
	struct sieve_t s;
	
	read_input(&num);

	if (num > 20)
		bound = sieve_bound(num);
	else
		bound = 100;

	s = init_sieve(bound);

	res = nth_prime(&s, num);

	free_sieve(&s);

	printf("%llu\n", res);
}
#endif