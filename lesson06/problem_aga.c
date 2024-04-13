/*
Problem AGA — распознавание ассемблера ARM
Ниже приведена некая функция foo(x, y)

foo:
        mov     x6, x0                  // arr = x
        ldr     w0, [x0]                // res = *x
        cmp     w1, 1                   // 
        ble     .L1                     // if y <= 1 goto .L1
        mov     x3, 1                   // i = 1
        mov     w2, w3                  // w2 = 1
        mov     w7, w3                  // w7 = 1
.L6:
        ldr     w4, [x6, x3, lsl 2]     // w4 = *(arr + i << 2)
        sub     w5, w2, #1              // w5 = w2 - 1
        add     x3, x3, 1               // i += 1
        cmp     w4, w0                  // if res != w4
        csinc   w2, w5, w2, ne          // w2 = w5, else w2++
        cmp     w2, 0                   // if w2 == 0 {
        csel    w0, w4, w0, eq          // res = w4
        csel    w2, w2, w7, ne          // w2 = 1 }
        cmp     w1, w3                  // if y > i goto .L6
        bgt     .L6
.L1:
        ret
Вам нужно догадаться что это за функция и написать её на языке C.

Ответом должна быть только foo, функцию main писать не надо.
*/
#include <stdio.h>

int foo(const int *a, int size)
{
    int res = a[0];

    if (size <= 1)
        return res;

    for (int i = 1, j = 1; i < size; ++i)
    {
        if (res != a[i])
            --j;
        else
            ++j;
        
        if (!j)
        {
            res = a[i];
            j = 1;
        }
    }

    return res;
}


int main()
{
    int a[] = {9, 3, 4, 3, 2, 4, 4, 2, 4, 4};

    int x = foo(a, sizeof(a)/sizeof(int));

    printf("%d\n", x);
}