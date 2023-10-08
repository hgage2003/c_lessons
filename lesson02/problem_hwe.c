#define TEST 1

#if TEST
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>
#include <limits.h>
#include <math.h>

struct sieve_t {
  int n;
  unsigned char *mod1;
  unsigned char *mod5;  
};

void fill_sieve(struct sieve_t *sv);
int is_prime(struct sieve_t *sv, unsigned n);

struct sieve_t init_sieve(unsigned size_bytes)
{
    struct sieve_t sv;
    sv.mod1 = calloc(size_bytes, sizeof(unsigned char));
    sv.mod5 = calloc(size_bytes, sizeof(unsigned char));

    if ((sv.mod1  == 0) || (sv.mod5  == 0))
    {
        printf("Error: calloc error\n");
        abort();
    }
    sv.n = size_bytes;
    
    fill_sieve(&sv);

    return sv;
}

void free_sieve(struct sieve_t *sv)
{
    assert(sv != 0);
    free(sv->mod1);
    free(sv->mod5);
    sv->n = 0;
}

unsigned long long sieve_bound(unsigned num)
{
	assert(num > 20);
	double dnum = num;
	double dres = dnum * (log(dnum) + log(log(dnum)));
	return (unsigned long long) round(dres);
}

unsigned long long nth_prime(struct sieve_t *sv, unsigned N)
{
	unsigned res = 0, counter = 2; // 2 and 3

	assert(N > 0);

    if (N == 1)
        return 2;

    if (N == 2)
        return 3;

	for (;;)
    {
		counter += is_prime(sv, res + 1);
        if (counter >= N)
            return (res + 1);
            
        counter += is_prime(sv, res + 5);
        if (counter >= N)
            return (res + 5);

        res += 6;
    }
}

void read_input(unsigned *n)
{
	int ninput = scanf("%ud", n);
	if (ninput != 1 || (*n < 1))
	{
		printf("Error: wrong input\n");
		abort();
	}
}

#endif

int is_prime(struct sieve_t *sv, unsigned n)
{
    unsigned mod = n % 6, div = n / 6;
    unsigned byte, bit;
    unsigned char prime;

    if ((n == 2) || (n == 3))
        return 1;

    if ((mod != 1) && (mod != 5))
        return 0;

    byte = div / CHAR_BIT; bit = div % CHAR_BIT;
    
    if (mod == 1)
        prime = !((sv->mod1[byte] >> bit) & 1u);
    else
        prime = !((sv->mod5[byte] >> bit) & 1u);
    
    return prime;   
}

void set_not_prime(struct sieve_t *sv, unsigned n)
{
    unsigned mod = n % 6, div = n / 6;
    unsigned byte, bit;

    if ((mod != 1) && (mod != 5))
        return;

    byte = div / CHAR_BIT; bit = div % CHAR_BIT;

    if (mod == 1)
        sv->mod1[byte] |= 1u << bit;
    else
        sv->mod5[byte] |= 1u << bit;
}

void fill_sieve(struct sieve_t *sv)
{
    unsigned sieve_max = sv->n * CHAR_BIT * 6;
    sv->mod1[0] = (unsigned char)1; // 1 - составное
    
    for (unsigned i = 0; i * i < sieve_max; i += 6)
    {
        if (is_prime(sv, i + 1))
            for (unsigned j = (i + 1) * 2; j < sieve_max; j += (i + 1))
                set_not_prime(sv, j);

        if (is_prime(sv, i + 5))
            for (unsigned j = (i + 5) * 2; j < sieve_max; j += (i + 5))
                set_not_prime(sv, j);
    }
}

#if TEST

int main()
{
	unsigned num;
	unsigned bound, res = 0;
	struct sieve_t s;
	
	read_input(&num);

	if (num > 20)
		bound = sieve_bound(num);
	else
		bound = 100;

	s = init_sieve(bound / (CHAR_BIT * 6));

	res = nth_prime(&s, num);

	free_sieve(&s);

	printf("%u\n", res);
}

#endif