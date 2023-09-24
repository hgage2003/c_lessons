#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 32

void read_input(unsigned int *x, unsigned int *y)
{
	int ninput;
	ninput = scanf("%u%u", x, y);
	if (ninput != 2 || *y >= 11 || *x == 0 || *y == 0)
	{
		printf("error: wrong input\n");
		abort();
	}
}

int main(void)
{
	unsigned int x, y, len = 0;

	read_input(&x, &y);

	char reversed_val[MAXLEN];
	do
	{
		reversed_val[len++] = x % y;
		x /= y;
	}
	while (x);

	for (; len > 0; len--)
		printf("%d", reversed_val[len - 1]);

	printf("\n");
}
