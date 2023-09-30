#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void read_input(int *n)
{
	int ninput;
	ninput = scanf("%d", n);
	if (ninput != 1 || *n < 1)
	{
		printf("Error: wrong input\n");
		abort();
	}
}

// P algorithm
unsigned char is_prime(unsigned long long n)
{
	if (n < 2)
		return 0;

	for (unsigned long long i = 2; i * i <= n; ++i)
		if ((n % i) == 0)
			return 0;

	return 1;
}

int main()
{
	int n;
	unsigned long long result = 2;

	read_input(&n);
	assert(n > 0);
	
	while (--n > 0)
		while (!is_prime(++result))
			;

	printf("%llu\n", result);
}