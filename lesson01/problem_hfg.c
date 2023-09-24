#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GAME_LEN 200

void read_input(int *t, int *p)
{
    int ninput;
    ninput = scanf("%d%d", t, p);
    if ((ninput != 2) || (*p < 1) || (*p > 2) || (*t < 2))
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

int player_turn(int total, int possible)
{
    int ninput, turn;
    printf("[total %d, possible %d] Your turn: ", total, possible);
    ninput = scanf("%d", &turn);
    if (ninput != 1 || turn > possible)
    {
        printf("error: wrong input\n");
        turn = player_turn(total, possible); // dont think abort() better in this place
    }
    return turn;
}

void print_status(int total, int turn)
{
    static char game[GAME_LEN] = {0};
    char chturn[13];
    char delim = (total == turn) ? '!' : ',';

    if (game[0] == 0)
        sprintf(game, "%d.", total);

    sprintf(chturn, "%d%c", turn, delim);
    if (strlen(game) + strlen(chturn) < GAME_LEN)
        strcat(game, chturn);

    printf("%s\n", game);
}

int main()
{
    int total, possible, player, turn; // player - 1 user, 2 computer

    read_input(&total, &player);
    // player - 0 user, !0 computer
    --player;
    possible = total - 1;

    while (total > 0)
    {
        if (player == 0)
            turn = player_turn(total, possible);
        else
        {
            turn = next_turn(total, possible);
            printf("My turn: %d\n", turn);
        }

        possible = turn * 2;
        player = (++player) % 2;

        print_status(total, turn);
        total -= turn;
    }

   if (player != 0) // turn changed
        printf("WIN\n");
    else
        printf("LOOSE\n");
}