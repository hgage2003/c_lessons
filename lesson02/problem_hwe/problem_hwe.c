#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>		// CHAR_BIT
#include "bit_sieve.h"
#include "simple-bench.h"

unsigned long long nth_prime(struct sieve_t *sv, unsigned long long N)
{
	unsigned long long counter = 2; // 2 and 3
	unsigned long long res = 0;

	assert(N > 0);

	if (N == 1)
		return 2;

	if (N == 2)
		return 3;

	for (;;)
	{
		counter += is_prime(sv, res + 1);
		if (counter >= N)
			return (res + 1);
			
		counter += is_prime(sv, res + 5);
		if (counter >= N)
			return (res + 5);
		
		res += 6;
	}
}

void read_input(unsigned long long *n)
{
	int ninput = scanf("%llu", n);
	if (ninput != 1 || (*n < 1))
	{
		printf("Error: wrong input\n");
		abort();
	}
}

int main()
{
	unsigned long long num, bound, res;
	struct sieve_t* s;
	struct timespec tm1, tm2;

	read_input(&num);
	bound = sieve_bound(num);

	simple_gettime(&tm1);
	s = init_sieve(bound / (CHAR_BIT * 6) + 1);
	simple_gettime(&tm2);
	#if 1
		printf("time to build sieve: %f\n", diff(tm1, tm2));
	#endif

	res = nth_prime(s, num);
	free_sieve(s);
	printf("%llu\n", res);
}
