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
	free(s->sieve);
	s->sieve = 0;
	s->size = 0;
}
 
unsigned char is_prime(struct sieve_t s, unsigned n)
{
	assert(n < s.size);
	return(s.sieve[n] == 1) ? 0 : 1;
}

void read_input(unsigned *n)
{
	int ninput = scanf("%ud", n);
	if (ninput != 1 || (*n < 2))
	{
		printf("Error: wrong input\n");
		abort;
	}
}

int main()
{
	unsigned num;
	unsigned long long bound, res = 0;
	struct sieve_t s;
	
	read_input(&num);

	s = init_sieve(num + 1);

	for (unsigned i = 2; i <= num; ++i)
		res += is_prime(s, i);

	free_sieve(&s);

	printf("%llu\n", res);
}
