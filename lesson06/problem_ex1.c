/*
Задача со слайда на 44:15

Распознайте функцию

foo:    test esi, esi                       // foo (int *x, int y)
        jle .L4                             // if (y <= 0) goto .L4
        lea eax, -1[rsi]                    //
        lea rdx, 4[rdi+rax*4]               // z = x + y;
        xor eax, eax                        // eax = 0 

.L3     add eax, DWORD PTR [rdi]            // eax += *x;
        add rdi, 4                          // *x = eax
        mov DWORD PTR -4[rdi], eax          // x++
        cmp rdi, rdx                        // if (x != z)
        jne .L3                             // goto L3
        ret                                 

.L4     xor eax, eax                        // return 0
        ret
*/

int foo(int *x, int y)
{
    int sum = 0;
    if (y <= 0)
        return 0;

    for (int i = 0; i < y; i++)
    {
        sum += x[i];
        x[i] = sum;
    }

    return sum;
}