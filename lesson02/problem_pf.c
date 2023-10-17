#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <malloc.h>
#include <limits.h>

const int NUM_TRIES = 100;
const unsigned int SIEVE_SIZE = 100000;

struct sieve_t {
  int n;
  unsigned char *mod1;
  unsigned char *mod5;  
};

void read_input(unsigned*, unsigned*);
struct sieve_t init_sieve(unsigned);
void free_sieve(struct sieve_t*);
int is_prime(struct sieve_t, unsigned long long);

int main()
{
    unsigned k, n;
    unsigned long long res = 0, sp = 0, s = 1;
    struct sieve_t sv;

    read_input(&k, &n);
    srand(time(NULL));

    sv = init_sieve(SIEVE_SIZE / (CHAR_BIT * 6));

    while (s < (2ull << 60))
    {
        unsigned long long temp = s;
        s = k * s + n * sp;
        sp = temp;

        if (is_prime(sv, s))
            res = s;
    }

    free_sieve(&sv);
    printf("%llu\n", res);
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

int is_prime_fermat(unsigned long long);
int is_prime(struct sieve_t sv, unsigned long long n)
{
    unsigned mod = n % 6, div = n / 6;
    unsigned byte, bit;
    unsigned char prime;

    if (n >= SIEVE_SIZE)
        return is_prime_fermat(n);

    if ((n == 2) || (n == 3))
        return 1;

    if ((mod != 1) && (mod != 5))
        return 0;

    byte = div / CHAR_BIT; bit = div % CHAR_BIT;
    
    if (mod == 1)
        prime = !((sv.mod1[byte] >> bit) & 1u);
    else
        prime = !((sv.mod5[byte] >> bit) & 1u);
    
    return prime;   
}

void fill_sieve(struct sieve_t *sv)
{
    unsigned sieve_max = sv->n * CHAR_BIT * 6;
    sv->mod1[0] = (unsigned char)1; // 1 - составное
    
    for (unsigned i = 0; i * i < sieve_max; i += 6)
    {
        if (is_prime(*sv, i + 1))
            for (unsigned j = (i + 1) * 2; j < sieve_max; j += (i + 1))
                set_not_prime(sv, j);

        if (is_prime(*sv, i + 5))
            for (unsigned j = (i + 5) * 2; j < sieve_max; j += (i + 5))
                set_not_prime(sv, j);
    }
}

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

unsigned long long mulmod(unsigned long long a, unsigned long long b, unsigned long long mod)
{
    unsigned long long res = 0;
    while (a > 0)
    {
        if (a & 1)
            res = (res + b) % mod;

        a >>= 1;
        b = (b << 1) % mod;
    }

    return res;
}

unsigned long long pow_mod(unsigned long long x, unsigned long long n, unsigned long long mod)
{
    unsigned long long prod = 1, mult = x % mod;
    
    while (n > 0)
    {
        if (n & 1)
            prod = mulmod(prod, mult, mod);

        mult = mulmod(mult, mult, mod);
        n >>= 1;
    }

    return prod;
}

int is_prime_fermat(unsigned long long num)
{
    int is_prime = 1;

    for (int i = 0; i < NUM_TRIES; ++i)
    {
        unsigned long long test_num = rand() % (num - 2) + 2;
        is_prime = (pow_mod(test_num, num - 1, num) == 1);
        if (is_prime == 0)
            break;
    }

    return is_prime;
}

void read_input(unsigned *k, unsigned *n)
{
    int ninput = scanf("%u%u", k, n);
    if (ninput != 2 || (k == 0) || (n == 0))
    {
        printf("Error:wrong input\n");
        abort();
    }
}