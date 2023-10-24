#pragma once

#include <malloc.h>
#include <limits.h>     // CHAR_BIT
#include <math.h>       // log()
#include <stdlib.h>     // abort()

struct sieve_t {
  unsigned long long n;
  unsigned char *mod1;
  unsigned char *mod5;  
};

int is_prime(struct sieve_t *sv, unsigned long long n)
{
    // mod определяет в каком массиве бит, div - номер бита 
    unsigned long long mod = n % 6, div = n / 6;
    unsigned long long byte, bit;
    unsigned char prime;

    if ((n == 2) || (n == 3))
        return 1;

    if ((mod != 1) && (mod != 5))
        return 0;

    byte = div / CHAR_BIT; bit = div % CHAR_BIT;
    
    if (mod == 1)
        prime = !((sv->mod1[byte] >> bit) & 1);
    else
        prime = !((sv->mod5[byte] >> bit) & 1);
    
    return prime;   
}

void set_not_prime(struct sieve_t *sv, unsigned long long n)
{
    unsigned long long mod = n % 6, div = n / 6;
    unsigned long long byte, bit;

    if ((mod != 1) && (mod != 5))
        return;

    byte = div / CHAR_BIT; bit = div % CHAR_BIT;

    if (mod == 1)
        sv->mod1[byte] |= (1 << bit);
    else
        sv->mod5[byte] |= (1 << bit);
}

void fill_sieve(struct sieve_t *sv)
{
    unsigned long long sieve_max = sv->n * CHAR_BIT * 6;
    sv->mod1[0] = (unsigned char)1; // 1 - составное
    
    for (unsigned long long i = 0; (i * i) < sieve_max; i += 6)
    {
        if (is_prime(sv, i + 1))
            for (unsigned long long j = (i + 1) * 2; j < sieve_max; j += (i + 1))
                set_not_prime(sv, j);

        if (is_prime(sv, i + 5))
            for (unsigned long long j = (i + 5) * 2; j < sieve_max; j += (i + 5))
                set_not_prime(sv, j);
    }
}

struct sieve_t init_sieve(unsigned long long size_bytes)
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
    if (!sv)
        return;

    free(sv->mod1);
    free(sv->mod5);
    sv->n = 0;
}

unsigned long long sieve_bound(unsigned long long num)
{
	double dnum = num, dres;
    
    if (num < 20)
        return 100;
        
	dres = dnum * (log(dnum) + log(log(dnum)));
	return (unsigned long long) round(dres);
}