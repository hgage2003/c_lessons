#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void read_input(int *x, int *n, int *m)
{
	int ninput;
	ninput = scanf("%d%d%d", x, n, m);
	if (ninput != 3 || m == 0)
	{
		printf("error: wrong input\n");
		abort();
	}
}

int pow_mod(int x, int n, int mod)
{
	int prod = 1, mult = x % mod;

	assert(mod != 0);

	while (n > 0)
	{
		if ((n % 2) == 1)
		{
			prod = (prod * mult) % mod;
			n -= 1;
		}

		mult = (mult * mult) % mod;
		n /= 2; 
	}

	return prod;
}

int main(void)
{
	int x, n, m, res;

	read_input(&x, &n, &m);

	res = x;
	for (;n > 1; --n)
	{
		res = pow_mod(res, x, m);
	}
	
	printf("%d\n", res);
}
