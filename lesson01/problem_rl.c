#include <stdio.h>
#include <stdlib.h>

long long iabs(long long x) { return (x < 0) ? -x : x; };
long long eu_mod(long long x, long long y) { long long res = x % y; if (res < 0) res += iabs(y); return res; }

void read_input(long long *px, long long *py)
{
	int ninput;
	ninput = scanf("%lld%lld", px, py);
	if (ninput != 2)
	{
		printf("Error: wrong input\n");
		abort();
	}
}

long long gcd(long long x, long long y)
{
	long long g;

	// gcd(x, 0) == x, gcd(0,0) == 0
	if (x == 0)
		return y;
	if (y == 0)
		return x;

	do
	{
		g = eu_mod(x, y);
		x = y;
		y = g;
	} while (g != 0);

	return x;
}

int main()
{
	long long x = 0, y = 0, res;

	read_input(&x, &y);

	res = gcd(x, y);

	printf("%lld\n", res);
}