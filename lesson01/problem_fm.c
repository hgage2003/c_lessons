#include <stdio.h>
#include <stdlib.h>

void read_input(unsigned int *x, unsigned int *m)
{
	int ninput;
	ninput = scanf("%u%u", x, m);
	if (ninput != 2 || *m == 0)
	{
		printf("error: wrong input\n");
		abort();
	}
}

int main(void)
{
	unsigned int x, m, fm = 1, fmp = 0, temp;
	
	read_input(&x, &m);

	for (int i = 2; i <= x; i++)
	{
		temp = fm;
		fm = (fm + fmp) % m;
		fmp = temp;
	}

	if (x == 0)
		fm = 0;
	
	printf("%d\n", fm);
}
