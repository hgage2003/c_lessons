#include "bit_sieve.h"

#include <malloc.h>
#include <limits.h>     // CHAR_BIT
#include <math.h>       // log(), round()
#include <stdlib.h>     // abort()
#include <assert.h>

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

static void set_not_prime(struct sieve_t *sv, unsigned long long n)
{
    unsigned long long mod = n % 6, div = n / 6;
    unsigned long long byte, bit;

    assert ((mod == 1) || (mod == 5));

    byte = div / CHAR_BIT; bit = div % CHAR_BIT;

    if (mod == 1)
        sv->mod1[byte] |= (1 << bit);
    else
        sv->mod5[byte] |= (1 << bit);
}

// проверка каждого N из mod1, mod5
// если N простое, заполнение решета от 5N и 7N с шагом 6N
static void fill_sieve(struct sieve_t *sv)
{
    unsigned long long sieve_max = sv->n * CHAR_BIT * 6;
    sv->mod1[0] = 1; // 1 - составное
    
    for (unsigned long long i = 0; (i * i) < sieve_max; i += 6)
    {
        unsigned long long num[2] = {i + 1, i + 5};
        for (int i = 0; i < 2; ++i)
            if (is_prime(sv, num[i]))
            {
                unsigned long long step = num[i] * 6;
                unsigned long long it[2] = {num[i] * 5, num[i] * 7};
                for (int j = 0; j < 2; ++j)
                    for (; it[j] < sieve_max; it[j] += step)
                        set_not_prime(sv, it[j]);
            }
    }
}

struct sieve_t* init_sieve(unsigned long long size_bytes)
{
    struct sieve_t *sv = calloc(1, sizeof(struct sieve_t));
    if (!sv)
    {
        printf("Error: calloc error\n");
        abort();
    }

    sv->mod1 = calloc(size_bytes, sizeof(unsigned char));
    if (!sv->mod1)
    {
        printf("Error: calloc error\n");
        free(sv);
        abort();
    }

    sv->mod5 = calloc(size_bytes, sizeof(unsigned char));
    if (!sv->mod5)
    {
        printf("Error: calloc error\n");
        free(sv->mod1);
        free(sv);
        abort();
    }

    sv->n = size_bytes;
    
    fill_sieve(sv);

    return sv;
}

void free_sieve(struct sieve_t *sv)
{
    if (!sv)
        return;

    free(sv->mod1);
    free(sv->mod5);
    free(sv);
    sv = 0;
}

unsigned long long sieve_bound(unsigned long long num)
{
    double dnum = num, dres;

    if (num < 20)
        return 100;
        
    dres = dnum * (log(dnum) + log(log(dnum)));
    return (unsigned long long) round(dres);
}