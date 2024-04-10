/*
Problem AS2 — декодер
Регистровый файл состоит из четырёх восьмиразрядных регистров

Register file
Register	A	B	C	D
Encoding (binary)	00	01	10	11
Вам задана следующая система команд и таблица мнемоник

Instruction set
Mnemonic	Encoding (binary)
MOVI Imm — move constant to D register	0IIIIIII
ADD R, R — add two registers modulo 256	1000RRRR
SUB R, R — sub two registers modulo 256	1001RRRR
MUL R, R — mul two registers modulo 256	1010RRRR
DIV R, R — div two registers modulo 256	1011RRRR
IN R — read register R from keyboard	110000RR
OUT R — write register R to screen	110001RR
Вам необходимо распечатать hex ввод как текст программы

В случае ошибки в одной из команд, все предыдущие должны быть распечатаны верно


Пример 1

Вход: 0x70 0xc7 0xc1 0x87

Выход:

MOVI 112

OUT D

IN B

ADD B, D


Пример 2

Вход: 0x70 0xFF 0xc1 0x87

Выход:

MOVI 112

ERROR
*/

#include <stdio.h>
#include <string.h>
#include <assert.h>

void reg_name(char* str, unsigned char code)
{
    char reg = 0;
    assert(code >= 0 && code < 4);

    switch (code)
    {
        case 0:
            reg = 'A';
            break;
        case 1:
            reg = 'B';
            break;
        case 2:
            reg = 'C';
            break;
        case 3:
            reg = 'D';
            break;
        default:
            break;
    }

    str[0] = reg;
    str[1] = 0;
}

int decode(unsigned char code)
{
    char cmd_s[8] = {0}, r1_s[8] = {0}, r2_s[8] = {0};
    unsigned char ncmd = (code & 0xf0) >> 4,
        r1 = (code & 0xc) >> 2, r2 = code & 0x3;

    if (!(code & 0x80))
    {
        strcpy(cmd_s, "MOVI");
        printf("%s %d\n", cmd_s, code);
        return 0;
    }

    reg_name(r1_s, r1);
    reg_name(r2_s, r2);

    switch (ncmd)
    {
        case 0x8:
            strcpy(cmd_s, "ADD");
            break;
        case 0x9:
            strcpy(cmd_s, "SUB");
            break;
        case 0xa:
            strcpy(cmd_s, "MUL");
            break;
        case 0xb:
            strcpy(cmd_s, "DIV");
            break;
        case 0xc:
            if (r1)
                strcpy(cmd_s, "OUT");
            else
                strcpy(cmd_s, "IN");
            r1_s[0] = 0;
        break;
    }

    if (r1_s[0])
        printf("%s %s, %s\n", cmd_s, r1_s, r2_s);
    else if (r2_s[0])
        printf("%s %s\n", cmd_s, r2_s);
    else
    {
        printf("ERROR\n");
        return 1;
    }
    return 0;
}

int main()
{
    unsigned int code;
    while (scanf("%x", &code) == 1)
    {
        if (decode((unsigned char)code))
            break;
    }
}