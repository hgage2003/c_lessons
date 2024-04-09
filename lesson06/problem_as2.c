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

void reg_name(char* str, int code)
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

int decode(unsigned code)
{
    char cmd[8] = {0}, param1[8] = {0}, param2[8] = {0};
    int ncmd = (code & 0xf0) >> 4;
    int np1 = (code & 0xc) >> 2;
    int np2 = code & 0x3;

    assert(code == (code & 0xff));

    // MOVI
    if (!(code & 0x80))
    {
        strcpy(cmd, "MOVI");
        sprintf(param1, "%d", code);
        ncmd = 0xff;
    }

    switch (ncmd)
    {
        case 0x8:
            strcpy(cmd, "ADD");
            reg_name(param1, np1);
            reg_name(param2, np2);
            break;
        case 0x9:
            strcpy(cmd, "SUB");
            reg_name(param1, np1);
            reg_name(param2, np2);
            break;
        case 0xa:
            strcpy(cmd, "MUL");
            reg_name(param1, np1);
            reg_name(param2, np2);
            break;
        case 0xb:
            strcpy(cmd, "DIV");
            reg_name(param1, np1);
            reg_name(param2, np2);
            break;
        case 0xc:
            if (np1)
                strcpy(cmd, "OUT");
            else
                strcpy(cmd, "IN");
            reg_name(param1, np2);
        break;
    }

    if (param2[0])
        printf("%s %s, %s\n", cmd, param1, param2);
    else if (param1[0])
        printf("%s %s\n", cmd, param1);
    else
    {
        printf("ERROR\n");
        return 1;
    }
    return 0;
}

int main()
{
    unsigned code;
    while (scanf("%x", &code) == 1)
    {
        if (decode(code))
            break;
    }
}