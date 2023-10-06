#include <stdio.h>
#include <stdlib.h>

void read_input(unsigned *n)
{
    int ninput = scanf("%u", n);
    if ((ninput != 1) || (*n < 2))
    {
        printf("Error: wrong input\n");
        abort();
    }
}

unsigned gcd(unsigned long long a, unsigned long long b)
{
    unsigned long long q, r;

	do
	{
		r = a % b;
		q = a / b;
		a = b; b = r;
	}
	while (r != 0);

    return a;
}

int main()
{
    unsigned n;
    unsigned long long res = 2;
    read_input(&n);

    for (int i = 3; i <= n; ++i)
    {
        res = res * i / gcd(res, i);
    }

    printf("%llu\n", res);
}