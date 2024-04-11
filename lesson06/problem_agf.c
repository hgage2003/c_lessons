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
  mov eax, edi          // 
  imul  eax, edi        //           
  imul  eax, edi        // z = x * x * x;
  test  eax, eax        //  
  js  .L4               // if (z < 0) goto .L4
  ret                   // else return z;
.L4:
  imul  esi, esi        // 
  add edi, edi          // 
  mov edx, 17           //
  sub edx, edi          // 
  sub edx, esi          // 
  add eax, edx          // 
  ret                   // return z + 17 - x * 2 - y * y;
Вам нужно догадаться что это за функция и написать её на языке C.

Ответом должна быть только foo, функцию main писать не надо.
*/

#include <stdio.h>

int foo(int x, int y)
{
    int z = x * x * x;
 
    if (z < 0)
        z += 17 - x * 2 - y * y;

    return z;
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