#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct gcd_result
{
	long long d; // gcd
	long long a;
	long long b;
};

long long iabs(long long x) { return (x < 0) ? -x : x; }

long long eu_mod(long long x, long long y) { long long res = x % y; if (res < 0) res += iabs(y); return res; }

long long eu_div(long long x, long long y) { return (x - eu_mod(x, y)) / y; }

void read_input(long long *pa, long long *pb, long long *pc)
{
	int ninput;
	ninput = scanf("%lld%lld%lld", pa, pb, pc);
	if (ninput != 3)
	{
		printf("Error: wrong input\n");
		abort();
	}
}

struct gcd_result gcd_ee(long long x, long long y)
{
	long long q, r = y, rp = x, s = 0, sp = 1, t = 1, tp = 0, temp;
	struct gcd_result res;

	// if y == 0, gcd(x,y) == x
	if (y == 0)
	{
		res.d = x;
		res.a = 1;
		res.b = 0;
		return res;
	}

	// if x % y == 0 and y < 0 answer would be wrong
	// because alg will finish in one step and take negative y as d
	if (x % y == 0)
	{
		res.d = iabs(y);
		res.a = 0;
		res.b = res.d / y;
		return res;
	}	

	do
	{
		q = eu_div(rp, r);
		
		temp = r;
		r = eu_mod(rp, r); rp = temp;
		assert( r >= 0 );

		temp = s;
		s = sp - q * s; sp = temp;
		
		temp = t;
		t = tp - q * t; tp = temp;
	}
	while (r != 0);

	res.d = rp; res.a = sp; res.b = tp;

	return res;
}

int main()
{
	long long a, b, c;
	struct gcd_result res;

	read_input(&a, &b, &c);

	res = gcd_ee(a, b);
	if (c % res.d)
	{
		printf("NONE\n");
		return 0;
	}

	c /= res.d;

	printf("%lld %lld\n", res.a*c, res.b*c);
}
