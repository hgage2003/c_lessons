#include <stdio.h>
#include <stdlib.h>

void read_input(unsigned long long *x, unsigned long long *m)
{
	int ninput;
	ninput = scanf("%llu%llu", x, m);
	if (ninput != 2 || *m == 0)
	{
		printf("error: wrong input\n");
		abort();
	}
}

unsigned long long pisano_p(unsigned long long m)
{
	unsigned long long fm = 1, fmp = 0, pp = 0, temp;
	
	if ( m == 0 )
		return 0;
	if ( m == 1 )
		return 1;

	do
	{
		temp = fm;
		fm = (fm + fmp) % m;
		fmp = temp;
		++pp;
	} while ((fm != 1) || (fmp != 0) );

	return pp;
}

unsigned long long fibmod(unsigned long long x, unsigned long long m)
{
	unsigned long long fm = 1, fmp = 0, temp;

	for (unsigned long long i = 2; i <= x; i++)
	{
		temp = fm;
		fm = (fm + fmp) % m;
		fmp = temp;
	}

	if (x == 0)
		fm = 0;
	
	return fm;
}

int main(void)
{
	unsigned long long x, m, pp;
	
	read_input(&x, &m);

	pp = pisano_p(m);
	x %= pp;

	x = fibmod(x, m);
	
	printf("%llu %llu\n", x, pp);
}
