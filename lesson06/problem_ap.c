/*
Problem AP — простые числа на ассемблере
Ниже приведена функция наивной проверки числа на простоту на ассемблере (Linux, 64 bit)

// --- on entry edi = x (unsigned) ---
// --- returns 1 if prime, 0 if composite ---
start:
	mov	eax, 0
	cmp	edi, 1
	jbe	composite
	cmp	edi, 3
	jbe	prime
	test	dil, 1
	je	composite
	mov	ecx, 2

loop:

// --- Here something missing ---

  jne     loop

composite:
  mov     eax, 0
  ret
prime:
  mov     eax, 1
  ret
К сожалению, в этом листинге чего-то не хватает, а именно нескольких ассемблерных строчек в указанном месте

Допишите их так, чтобы процедура отработала корректно
*/

int prime(int i)
{
    if (i <= 1)
        return 0;

    if (i <= 3)
        return 1;

    if (!(i % 2))
        return 0;

    for (int j = 2; j < i; ++j )
    {   
        if (!(i % j))
            return 0;
    }
    
    return 1;
}

/*
Функция выше компилируется в такой код:

prime:
.LFB0:
	.cfi_startproc
	endbr64
	mov	eax, 0
	cmp	edi, 1
	jle	.L1
	mov	eax, 1
	cmp	edi, 3
	jle	.L1
	mov	eax, 0
	test	dil, 1
	je	.L1
	mov	ecx, 3
.L3:
	mov	eax, edi
	cdq
	idiv	ecx
	mov	eax, edx
	test	edx, edx
	je	.L1
	add	ecx, 1
	cmp	edi, ecx
	jne	.L3
	mov	eax, 1
.L1:
	ret
	.cfi_endproc

Так как в задаче последняя мнемоника в цикле jne     loop,
нужно немного его модифицировать руками (добавить переход в prime если j == i - 1):

mov	eax, edi
cdq
idiv	ecx
mov	eax, edx
test	edx, edx
je	composite
add	ecx, 1
cmp	edi, ecx
je      prime
*/