/*
    Problem RG — период генератора
    Заранее задан (определять его не надо) генератор f(x)

    typedef int (*generator_t)(int);
    Вам необходимо написать функцию с заранее заданной сигнатурой

    // определяет длину петли в генераторе
    unsigned cycle_len(generator_t gen);
    Генератор считает с нуля и в следующий раз принимает результат предыдущего вызова

    Вы можете быть уверены, что петля есть. Функция должна возвращать её длину

    В посылке должна быть только указанная функция, отправлять функцию main не нужно


    Пример 1

    Входная функция: f(x) = (x + 2) % 5

    Генерируемая последовательность: 0, 2, 4, 1, 3, 0, 2, ...

    Выход: 5


    Пример 2

    Входная функция: f(x) = (x + 2) % 5 + 1

    Генерируемая последовательность: 0, 3, 1, 4, 2, 5, 3, 1, 4 ...

    Выход: 5


    Пример 3

    Входная функция: f(x) = (x + 2) % 5 + 3

    Генерируемая последовательность: 0, 5, 5, 5, 5, ...

    Выход: 1


    Пример 4

    Входная функция: f(x) = (3 * x + 2) % 5 + 4

    Генерируемая последовательность: 0, 6, 4, 8, 5, 6 ...

    Выход: 4
*/

#ifdef NDEBUG
#include <stdio.h>

typedef int (*generator_t)(int);
#endif

// определяет длину петли в генераторе
unsigned cycle_len(generator_t gen)
{
    int r = 0, t = 0;
    int steps = 1, looplen = 0;

    for (; ; )
    {
        steps *= 2;
        for (int i = 0; i < steps; ++i)
        {
            r = gen(r);
            ++looplen;

            if (r == t)
                return looplen;
        }

        looplen = 0;
        t = r;
    }

    return 0;
}

#ifdef NDEBUG
int test1(int num)
{
    int ret = (num + 2) % 5;
    return ret;
}

int test2(int num)
{
    int ret = (num + 2) % 5 + 1;
    return ret;
}

int test3(int num)
{
    int ret = (num + 2) % 5 + 3;
    return ret;
}

int test4(int num)
{
    int ret = (3 * num + 2) % 5 + 4;
    return ret;
}

void print_gen10(generator_t gen)
{
    int num = 0;
    for (int i = 0; i < 10; ++i, num = gen(num))
        printf("%d ", num);

    printf("...\n");
}

int main()
{
    print_gen10(test1);
    printf("%d\n", cycle_len(test1));

    print_gen10(test2);
    printf("%d\n", cycle_len(test2));

    print_gen10(test3);
    printf("%d\n", cycle_len(test3));

    print_gen10(test4);
    printf("%d\n", cycle_len(test4));
}
#endif