/*
Problem AS — кодировщик
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
OUT R — write register R to screen      110001RR
Вам необходимо закодировать в hex пришедшие вам на stdin мнемоники

В случае ошибки в одной из них, все предыдущие должны быть закодированы верно


Пример 1

Вход:

MOVI 112

OUT D

IN B

ADD B, D

Выход: 0x70 0xc7 0xc1 0x87


Пример 2

Вход:

MOVI 112

OUT X

IN B

ADD B, D

Выход: 0x70 ERROR
*/

#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define BUFF_LEN 128

unsigned char decode(char *buffer, const regex_t *regex)
{
    int res;
    regmatch_t matches[4];
    char cmd_s[16] = {0}, p1_s[16] = {0}, p2_s[16] = {0};
    unsigned char r1 = 0, r2 = 0;
    
    if (buffer[0] == '\n')
        return 0;
        
    res = regexec(regex, buffer, 4, matches, 0);
    if (res)
        return 0xff;

    memcpy(cmd_s, buffer + matches[1].rm_so, matches[1].rm_eo - matches[1].rm_so);
    memcpy(p1_s, buffer + matches[2].rm_so, matches[2].rm_eo - matches[2].rm_so);

    if (matches[3].rm_eo > 0)
        memcpy(p2_s, buffer + matches[3].rm_so, matches[3].rm_eo - matches[3].rm_so);

    if (!strcmp("MOVI", cmd_s))
    {
        long i = strtol(p1_s, NULL, 10);
        return (unsigned char)i;
    }

    r1 = p1_s[0] - 'A';
    
    if (p2_s[0])
        r2 = p2_s[0] - 'A';

    if (!strcmp("ADD", cmd_s))
        return 0x80 | (r1 << 2) | r2;

    if (!strcmp("SUB", cmd_s))
        return 0x90 | (r1 << 2) | r2;
    
    if (!strcmp("MUL", cmd_s))
        return 0xa0 | (r1 << 2) | r2;

    if (!strcmp("DIV", cmd_s))
        return 0xb0 | (r1 << 2) | r2;

    if (!strcmp("IN", cmd_s))
        return 0xc0 | r1;

    if (!strcmp("OUT", cmd_s))
        return 0xc4 | r1;

    return 0xff;
}

int main()
{
    regex_t regex;
    char regerr[128];
    int res;
    char buffer[BUFF_LEN];

    char *regstr = "^[[:space:]]*(MOVI|ADD|SUB|MUL|DIV|IN|OUT)[[:blank:]]+"
                    "([[:digit:]]+|A|B|C|D)[[:blank:]]*"
                    ",?[[:blank:]]*(A|B|C|D)?[[:space:]]*$";

    res = regcomp(&regex, regstr, REG_EXTENDED);
    if (res) 
    {
        regerror(res, &regex, regerr, sizeof(regerr));
        fprintf(stderr, "Regex compilation failed: %s\n", regerr);
        abort();
    }

    
    while (fgets(buffer, BUFF_LEN, stdin))
    {
        unsigned char code = decode(buffer, &regex);
        if (code == 0xff)
        {
            printf("ERROR");
            break;
        }

        // 0 - код для пустых строк (не ошибка)
        if (code != 0)
            printf("0x%x ", code);
    }
    printf("\n");
    regfree(&regex);
}