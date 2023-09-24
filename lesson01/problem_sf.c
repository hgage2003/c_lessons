#include <stdio.h>
#include <stdlib.h>

int fs_rec(int num, int f, int fp)
{
    if (num >= (f + fp))
    {
        num = fs_rec(num, f + fp, f);
    }
    
    if (num < f)
	{
		printf("0");
        return num;
	}

	printf("1");
    return num - f;
}

void read_input(int *x)
{
	int ninput;
	ninput = scanf("%d", x);
	if (ninput != 1)
	{
		printf("error: wrong input\n");
		abort();
	}
}

int main(void)
{
	int x;
		
	read_input(&x);
	if (x == 0)
	{
		printf("0\n");
		return 0;
	}

	fs_rec(x, 1, 1);
	printf("\n");
}
