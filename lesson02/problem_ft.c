#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

const int NUM_TRIES = 100;

void read_input(unsigned long long *n)
{
    int ninput = scanf("%llu", n);
    if (ninput != 1)
    {
        printf("Error: wrong input\n");
        abort();
    }
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

int main()
{
    unsigned long long num;
    int is_prime = 1;
    read_input(&num);
    srand(time(NULL));

    for (int i = 0; i < NUM_TRIES; ++i)
    {
        unsigned long long test_num = rand() % (num - 2) + 2;
        is_prime = (pow_mod(test_num, num - 1, num) == 1);
        if (is_prime == 0)
            break;
    }

    printf("%d\n", is_prime);
}