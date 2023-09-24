#include <stdio.h>
#include <stdlib.h>

struct matrix2x2
{
	unsigned x00;
	unsigned x01;
	unsigned x10;
	unsigned x11;
};

struct matrix2x2 matrix_mult_mod(struct matrix2x2 a, struct matrix2x2 b, unsigned mod)
{
	struct matrix2x2 res;

	res.x00 = (a.x00 * b.x00 + a.x01 * b.x10) % mod;
	res.x01 = (a.x00 * b.x01 + a.x01 * b.x11) % mod;
	res.x10 = (a.x10 * b.x00 + a.x11 * b.x10) % mod;
	res.x11 = (a.x10 * b.x01 + a.x11 * b.x11) % mod;

	return res;
}

struct matrix2x2 matrix_pow_mod(struct matrix2x2 matr, unsigned pow, unsigned mod)
{
	struct matrix2x2 res = {1, 0, 0, 1}, mult = matr;

	while (pow > 0)
	{
		if ((pow % 2) == 1)
		{
			res = matrix_mult_mod(res, mult, mod);
			pow -= 1;
		}

		mult = matrix_mult_mod(mult, mult, mod);
		pow /= 2;
	} 

	return res;
}

void read_input(unsigned *x00, unsigned *x01, unsigned *x10, unsigned *x11, unsigned *n, unsigned *m)
{
	int ninput;
	ninput = scanf("%u%u%u%u%u%u", x00, x01, x10, x11, n, m);
	if ((ninput != 6) || (m == 0))
	{
		printf("error: wrong input\n");
		abort();
	}
}

int main(void)
{
	struct matrix2x2 matr, res = {1, 0, 0, 1};
	unsigned n, m;

	read_input(&matr.x00, &matr.x01, &matr.x10, &matr.x11, &n, &m);

	// identity matrix for n == 0
	if (n > 0)
		res = matrix_pow_mod(matr, n, m);

	printf("%u %u %u %u\n", res.x00, res.x01, res.x10, res.x11);
}