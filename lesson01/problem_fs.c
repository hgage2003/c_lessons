#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 50

void read_input(unsigned int *x)
{
	int ninput;
	ninput = scanf("%u", x);
	if (ninput != 1 || *x == 0)
	{
		printf("error: wrong input\n");
		abort();
	}
}

int main(void)
{
	unsigned int x, fact = 2, len = 0;
	char reversed_val[MAXLEN];
	
	read_input(&x);

	do
	{
		reversed_val[len++] = x % fact;
		x /= fact;
		++fact;
	}
	while (x);

	for (; len > 0; len--)
		printf("%d.", reversed_val[len - 1]);

	printf("\n");
}
