/*
Problem AGF — распознавание простой функции
Ниже приведена некая функция f(x, y)

// --- int f(int x, int y) ---
// edi = x
// esi = y
// return value = eax
  .globl  foo
  .type foo, @function
foo:
  mov eax, edi
  imul  eax, edi
  imul  eax, edi
  test  eax, eax
  js  .L4
  ret
.L4:
  imul  esi, esi
  add edi, edi
  mov edx, 17
  sub edx, edi
  sub edx, esi
  add eax, edx
  ret
Вам нужно догадаться что это за функция и написать её на языке C.

Ответом должна быть только foo, функцию main писать не надо.
*/

#include <stdio.h>

int foo(int x, int y)
{
    int a = x * x * x;
    int d = 17;

    if (a > 0)
        return a;

    y *= y;
    x += x;
    d -= (x + y);
    a += d;
    return a;
}

#ifdef NDEBUG
int main()
{
    int x[] = {-1, 1};
    int y[] = {0, 2};

    for (int i = 0; i < sizeof(x) / sizeof(int); ++i)
        printf("x = %d y = %d foo(x,y) = %d\n", x[i], y[i], foo(x[i], y[i]));
}
#endif