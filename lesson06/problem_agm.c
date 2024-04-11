/*
Problem AGM — распознавание более сложной функции
Ниже приведена некая функция foo(x, y, z)

// --- int foo(int *x, int y, int z) ---
// edi = x
// esi = y
// edx = z
// return value = eax
  .globl  foo
  .type foo, @function
foo:
  xor r8d, r8d                          // int v1 = 0
  test  edx, edx                        // if (z == 0)
  je  .L1                               // goto L1 
  mov eax, edx                          // int i = z - 1
  sub eax, 1                            //
  js  .L7                               // if (i < 0) goto .L7
  cdqe                                  // rax = eax
  jmp .L4                               // goto .L4
.L5:
  mov DWORD PTR 4[rdi+rax*4], edx       // x[i + 1] =  z
  sub rax, 1                            // i--
  test  eax, eax                        // if (i < 0) return v1
  js  .L1
.L4:
  mov edx, DWORD PTR [rdi+rax*4]        // z = x[i]
  mov r8d, eax                          // v1 = i
  cmp edx, esi                          // 
  jg  .L5                               // if (z > y) goto .L5     // while z > y
  add r8d, 1                            // v1++
.L1:
  mov eax, r8d                          // res = v1
  ret                                   // return res
.L7:
  mov r8d, edx                          // v1 = z
  jmp .L1                               // goto L1
Вам нужно догадаться что это за функция и написать её на языке C.

Ответом должна быть только foo, функцию main писать не надо.
*/

int foo(int *x, int y, int z)
{
    int res, v1 = z;

    if (z == 0)
        return 0;
    
    for (int i = z - 1; i >= 0; x[i + 1] = z, --i)
    {
        z = x[i];
        v1 = i;

        if (z <= y)
        {
            v1++;
            break;
        }
    }

    res = v1;
    return res;
}

#ifdef DEBUG
#include <stdio.h>

int main()
{
    int x[] = {1,2,3,4};
    int sx = sizeof(x) / sizeof(int);

    printf("%d\n", foo(x, 1, 2));
    for (int i = 0; i < sx; ++i)
        printf("%d ", x[i]);
    printf("\n");
}
#endif