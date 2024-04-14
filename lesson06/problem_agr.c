/*
Problem AGR — распознавание функции на RISC-V
Ниже приведена некая функция f(x, y, z)

foo:                        // int foo(int* arr, int first, int last)
        slli    a5,a1,32
        srli    t4,a5,30 
        add     t4,a0,t4 
        lw      t3,0(t4) 
        mv      a6,a0
        sext.w  a7,a2       // a7 = last
        bgeu    a1,a2,.L7   // if (first >= last) goto .L7
        slli    t1,a7,2
        add     a5,a0,t1    // a5 = arr + last * 4
        mv      a4,a7       // a4 = last
.L6:
        lw      a3,0(a5)
        add     a2,a6,t1    // a2 = arr + a7 * 4
        addiw   a4,a4,-1    // a4 -= 1
        ble     a3,t3,.L5   // if (*a5 <= arr[first]) goto .L5
        lw      a0,0(a2)    // temp = *a2
        addiw   a7,a7,-1    // a7 -= 1
        sw      a3,0(a2)    // *a2 = *a5
        sw      a0,0(a5)    // *a5 = a0
        slli    t1,a7,2
.L5:
        addi    a5,a5,-4    // a5 -= 4
        bltu    a1,a4,.L6   // if (first < a4) goto .L6
        lw      t3,0(t4)    
        add     a6,a6,t1
        lw      a5,0(a6)    // t = arr[a7]
        sw      t3,0(a6)    // arr[a7] = arr[first]
        sext.w  a0,a7
        sw      a5,0(t4)    // arr[first] = t
        ret                 // return a7
.L7:
        slli    t1,a7,2     
        add     a6,a6,t1
        lw      a5,0(a6)    // t = arr[a7]
        sw      t3,0(a6)    // arr[a7] = arr[first]
        mv      a0,a2
        sw      a5,0(t4)    // arr[first] = t
        ret                 // return last
Вам нужно догадаться что это за функция и написать её на языке C.

Ответом должна быть только foo, функцию main писать не надо.
*/

int foo(int* arr, int first, int last)
{
    int res = last, t;

    if (first >= last)
    {
        int t = arr[last];
        arr[last] = arr[first];
        arr[first] = t;
        return last;
    }

    for (int i = last; i > first; --i)
    {
        if (arr[i] > arr[first])
        {
            int t = arr[res];
            arr[res] = arr[i];
            arr[i] = t;
            --res;
        }     
    }

    t = arr[res];
    arr[res] = arr[first];
    arr[first] = t;
    return res;
}

#ifdef NDEBUG
#include <stdio.h>

int main()
{
        int x[] = {5, 6, 8, 4, 5, 6, 3, 8, 1, 2};
        int xs = sizeof(x) / sizeof(int);

        int res = foo(x, 0, xs - 1);

        for (int i=0; i < xs; ++i)
            printf("%d ", x[i]);
        printf("\n%d\n", res);

}
#endif