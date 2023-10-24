#pragma once

struct sieve_t {
  unsigned long long n;
  unsigned char *mod1;
  unsigned char *mod5;  
};

unsigned long long sieve_bound(unsigned long long num);
struct sieve_t init_sieve(unsigned long long size_bytes);
void free_sieve(struct sieve_t *sv);
int is_prime(struct sieve_t *sv, unsigned long long n);