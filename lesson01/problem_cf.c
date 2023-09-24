#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

long long iabs(long long x){ return (x < 0) ? -x : x; };
long long eu_mod(long long x, long long y) { long long res = x % y; if (res < 0) res += iabs(y); return res; }
long long eu_div(long long x, long long y) { return (x - eu_mod(x, y)) / y; }

void read_input(long long *px, long long *py)
{
	int ninput;
	ninput = scanf("%lld%lld", px, py);
	if (ninput != 2 || *py == 0)
	{
		printf("Error: wrong input\n");
		abort();
	}
}

int main()
{
	long long a, b, q, r;

	read_input(&a, &b);
	assert(b != 0);

	do
	{
		r = eu_mod(a, b);
		q = eu_div(a, b);
		printf("%lld ", q);
		a = b; b = r;
	}
	while (r != 0);

	printf("\n");
}
