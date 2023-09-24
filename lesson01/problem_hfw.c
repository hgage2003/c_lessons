#include <stdio.h>
#include <stdlib.h>

void read_input(int *t, int *p)
{
    int ninput;
    ninput = scanf("%d%d", t, p);
    if ((ninput != 2) || (p == 0) || (t == 0))
    {
        printf("error: wrong input\n");
        abort();
    }
}

int fs_rec(int num, int f, int fp, int *turn)
{
    if (num >= (f + fp))
    {
        num = fs_rec(num, f + fp, f, turn);
    }
    
    if (num < f)
        return num;

    if (num == f)
        *turn = f;

    return num - f;
}

int next_turn(int total, int possible)
{
    int turn = 0;

    if (possible >= total)
        return total;

    fs_rec(total, 1, 1, &turn);

    if (turn > possible)
        return 1;

    return turn;
}

int main()
{
    int total, possible, turn;

    read_input(&total, &possible);
    turn = next_turn(total, possible);

    printf("%d\n", turn);
}