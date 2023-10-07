#include <stdio.h>
#include <stdlib.h>

void read_input(unsigned long long *n)
{
    int ninput = scanf("%llu", n);
    if (ninput != 1)
    {
        printf("Error: wrong input\n");
        abort();
    }
}

int main()
{
    unsigned long long int n;
    int min = -1, max = -1, shift = 0;

    read_input(&n);

    while (n != 0)
    {
        char bit = n & 1;

        if (bit && (min < 0))
            min = shift;
        if (bit)
            max = shift;

        n >>= 1;
        ++shift;

#if 0
        printf("%llx\n", n);
#endif
    }

    if (max < 0)
        printf("-1\n");
    else
        printf("%d %d\n", max, min);
}