/*
Problem EX — работа с битами плавающих чисел
Вам дано число с плавающей точкой типа float (мантисса 23 нижних бита)

Вы должны получить из него другое число с плавающей точкой, инвертировав все нечётные биты
фракции (нулевой бит считается чётным) и напечатать с точностью до пятого знака после запятой


Пример 1:

Вход: 1.0

Выход: 1.33333

Пояснение: представление 1 это 0x3f800000, фракция это все нули, инверсия нечётных битов фракции
даёт 0x3faaaaaa


Пример 2:

Вход: 1.23456

Выход: 1.41152

Пояснение: представление 1.23456 это 0x3f9e0610, фракция это 0x1e0610, инверсия нечётных битов
фракции даёт 0x3fb4acba


Пример 3:

Вход: 0.00567

Выход: 0.00450 (на самом деле результат 0.004498, но ".5f" округлит до пятого знака)


Пример 4:

Вход: 124.5

Выход: 105.83333


Пример 5:

Вход: 102345

Выход: 121500.32812
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned fl_as_uns(float f)
{
    unsigned u;
    memcpy(&u, &f, sizeof(f));
    return u;
}

float uns_as_fl(unsigned u)
{
    float f;
     memcpy(&f, &u, sizeof(f));
     return f;
}

float invert(float f)
{
    unsigned u = fl_as_uns(f);
    u = (u & 0xffd55555) | ((~u) & 0x002aaaaa);
    f = uns_as_fl(u);
    return f;
}

int main()
{
    int res;
    float f;

    res = scanf("%f", &f);
    if (res != 1)
    {
        fprintf(stderr, "Error in input\n");
        abort();
    }

    f = invert(f);

    printf("%.5f\n", f);
}