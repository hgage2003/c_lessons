/*
Problem RP — верхняя и нижняя границы
Для этой задачи, установите округление вниз (FE_DOWNWARD)

На стандартном вводе числитель и знаменатель дроби

На выходе нижняя (по направлению к нулю) и верхняя (к бесконечности или минус бесконечности)
аппроксимации при представлении в формате float как два шестнадцатиричных числа: экспонента и
дробная часть мантиссы

Если возможно точное представление, на выходе только оно


Пример:

Вход: 1 3

Выход: 0x7d 0x2aaaaa 0x7d 0x2aaaab


Пример:

Вход: -1 3

Выход: 0x7d 0x2aaaab 0x7d 0x2aaaac


Пример:

Вход: 1 2

Выход: 0x7e 0x0


Пример:

Вход: 231 546

Выход: 0x7d 0x589d89 0x7d 0x589d8a
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fenv.h>

unsigned fl_as_uns(float f)
{
    unsigned u;
    memcpy(&u, &f, sizeof(f));
    return u;
}

int main()
{
    int res, numer, denom, prev_round;
    unsigned u, exp, mantl, manth;
    float f, fu;

    res = scanf("%d", &numer);
    if (res != 1)
    {
        fprintf(stderr, "Error in input\n");
        abort();
    }

    res = scanf("%d", &denom);
    if (res != 1)
    {
        fprintf(stderr, "Error in input\n");
        abort();
    }

    prev_round = fegetround();
    fesetround(FE_DOWNWARD);
    f = ((float)numer) / denom;
    fesetround(FE_UPWARD);
    fu = ((float)numer) / denom;
    fesetround(prev_round);

    u = fl_as_uns(f);
    exp = (u & 0x7f800000) >> 23;
    mantl = u & 0x007fffff;
    manth = mantl;

    if (u != fl_as_uns(fu))
    {
        if (f > 0)
            ++manth;
        else
            --mantl;
    }

    printf("0x%x 0x%x ", exp, mantl);
    if (manth != mantl)
        printf("0x%x 0x%x ", exp, manth);
    printf("\n");
}