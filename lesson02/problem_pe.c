#define TEST 1

#if TEST
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <limits.h>

struct sieve_t 
{
  int n;
  unsigned char *s;
};

void fill_sieve(struct sieve_t *sv);

struct sieve_t init_sieve(unsigned int size_bytes)
{
    struct sieve_t sv;
    sv.s = calloc(size_bytes, sizeof(unsigned char));
    if (sv.s == 0)
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
    free(sv->s);
    sv->n = 0;
}
#endif

int is_prime(struct sieve_t *sv, unsigned n)
{
    unsigned byte, bit, prime;
    assert(sv && (n < (sv->n * CHAR_BIT)));
    
    byte = n / CHAR_BIT;
    bit = n % CHAR_BIT;

    prime = !((sv->s[byte] >> bit) & 1);

    return prime;
}

void fill_sieve(struct sieve_t *sv)
{
    int sieve_size = sv->n * CHAR_BIT;

    sv->s[0] |= 3u; // 0 и 1 - составные
    for (unsigned int i = 2; i * i <= sieve_size; ++i)
    {
        if (!is_prime(sv, i))
            continue;

        for (int j = i * 2; j < sieve_size; j += i)
        {
            unsigned byte = j / CHAR_BIT, bit = j % CHAR_BIT;
            sv->s[byte] |= (1 << bit);
        }
    }
}

#if TEST
int main()
{
    struct sieve_t sv = init_sieve(1024);
    
    for (int i = 1; i < 100; ++i)
        if (is_prime(&sv, i))
            printf("Number %d is prime\n", i);
        else
            printf("Number %d is not prime\n", i);
    
    free_sieve(&sv);
}
#endif