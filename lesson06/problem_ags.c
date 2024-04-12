/*
Problem AGS — распознавание вызова функции
Ниже приведена некая функция caller в System V AMD ABI, вызывающая из себя функцию callee

  .text
  .globl  caller                            // caller(int x, int y, int z)
  .type caller, @function
caller:
  push  r13                                 // v4
  push  r12                                 // v1
  push  rbp                                 // 
  push  rbx
  sub rsp, 8
  mov r12d, 1                               // int v1 = 1
  test  esi, esi                            // 
  je  .L1                                   // if (y == 0) goto .L1 // => return v1;
  mov eax, edi                              // int v2 = x
  mov ebx, esi                              // int v3 = y
  mov r13d, edx                             // int v4 = z
  mov edx, 0                                // prepare for div
  div r13d                                  // v2 /= v4
  mov rbp, rdx                              // int v5 = v2 % v4
  mov r12d, 1                               // v1 = 1
  jmp .L5
.L3:
  mov edi, ebp                              // 1st arg = v5
  mov edx, r13d                             // 3rd arg = v4
  mov esi, ebp                              // 2nd arg = v5
  call  callee                              //
  mov ebp, eax                              // v5 = callee(v5, v5, v4)
  shr ebx                                   // v3 /= 2
.L4:
  test  ebx, ebx                            // {if v3 == 0
  je  .L1                                   // goto .L1 // => return v1
.L5:
  test  bl, 1                               // if (!(v3 % 2))
  je  .L3                                   // {L3}, else
  mov edx, r13d                             // 3rd arg = v4 
  mov esi, ebp                              // 2nd arg = v5
  mov edi, r12d                             // 1st arg = v1
  call  callee                              // 
  mov r12d, eax                             // v1 = callee(v1, v5, v4)
  sub ebx, 1                                // --v3
  jmp .L4                                   // }
.L1:
  mov eax, r12d
  add rsp, 8
  pop rbx
  pop rbp
  pop r12
  pop r13
  ret                                       // return v1
Вам нужно догадаться что это за функция и написать её на языке C.

Ответом должна быть только caller, функции main и callee писать не надо.
*/
int callee(int x, int y, int z);

unsigned caller(unsigned n, unsigned k, unsigned m)
{
    unsigned res = 1, v5;
    if (!k)
        return res;

    n %= m;
   
    for (res = 1; k != 0; --k)
    {
        if (!(k % 2))
        {
            n = callee(n, n, m);
            k /= 2;
        }

        res = callee(res, n, m);
    }
    
    return res;
}

int callee(int x, int y, int z)
{
    for (int i = 0; i < y; ++i)
        if (i%2)
            x += z;
    return x;
}