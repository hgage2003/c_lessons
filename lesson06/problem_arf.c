/*
Problem ARF — распознавание floating point функции
Ниже приведена некая функция f

  .globl  foo
  .type foo, @function
foo:
  mov       edi, edi                 // ?
  pxor      xmm1, xmm1               // 
  sub       rsp, 24                  // 
  cvtsi2sd  xmm1, rdi                // 
  movapd    xmm0, xmm1               // 
  movsd     QWORD PTR [rsp], xmm1    // float a = x
  call      log                      // 
  movsd     QWORD PTR [rsp+8], xmm0  // float b = log(x)
  movsd     xmm0, QWORD PTR [rsp]    // 
  call      log                      // 
  call      log                      // res = log(log(x))
  addsd     xmm0, QWORD PTR [rsp+8]  // res += log(x)
  mulsd     xmm0, QWORD PTR [rsp]    // res *= x
  call      round                    // 
  add       rsp, 24
  cvttsd2si rax, xmm0                // return round(res)
  ret
Вам нужно догадаться что это за функция и написать её на языке C.

Ответом должна быть только foo, функцию main писать не надо.
*/
#include <math.h>

long foo(unsigned x)
{
    double fx = x, tmp = log(fx), res;
    res = log(tmp);
    res += tmp;
    res *= fx;
    return round(res);
} 