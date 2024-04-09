/*
Problem MK — эмулятор
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
Вам приходит закодированная программа как параметр argv[1] и стандартный ввод на stdin

Вам необходимо симулировать работу программы и вывести всё что она выводит на stdout


Пример 1

Программа: 0x70 0xc7 0xc1 0x87 0x27 0xc5 0x8d 0xc1 0x87 0x6f 0xc5 0xc7

Вход:104 64

Выход:112 216 63 111

Пояснение: программа состоит (если записать её символически) из следующих команд

MOVI 112    D = 112

OUT D       output 112

IN B        read 104

ADD B, D    B = 104 + 112

MOVI 39     D = 39

OUT B       output 216

ADD D, B    D = 216 + 39

IN B        read 64

ADD B, D    B = (216 + 39 + 64) mod 256

MOVI 111    D = 111

OUT B       output 63

OUT D       output 111
*/

#include <stdio.h>
#include <stdlib.h>

enum cmd {MOVI, ADD, SUB, MUL, DIV, IN, OUT, ERROR};

union param_t
{
    enum reg {A, B, C, D} registers[2];
    unsigned char imm;
};

struct mnemo_t
{
    enum cmd command;
    union param_t parameter;
};

struct mnemo_t decode(unsigned char code)
{
    struct mnemo_t res;
    unsigned char ncmd = (code & 0xf0) >> 4;
    unsigned char np1 = (code & 0xc) >> 2;
    unsigned char np2 = code & 0x3;

    // MOVI
    if (!(code & 0x80))
    {
        res.command = MOVI;
        res.parameter.imm = code;
        return res;
    }

    res.parameter.registers[0] = np1;
    res.parameter.registers[1] = np2;
    
    switch (ncmd)
    {
        case 0x8:
            res.command = ADD;
            break;
        case 0x9:
            res.command = SUB;
            break;
        case 0xa:
            res.command = MUL;
            break;
        case 0xb:
            res.command = DIV;
            break;
        case 0xc:
            if (np1 == 1)
                res.command = OUT;
            else if (np1 == 0)
                res.command = IN;
            else
                res.command = ERROR;
        break;
        default:
            res.command = ERROR;
            break;
    }

    return res;
}

int execute(const struct mnemo_t *cmd, unsigned char machine[4])
{
    int res;
    unsigned tmp_in;

    switch (cmd->command)
    {
        case MOVI:
            machine[D] = cmd->parameter.imm;
            break;
        case ADD:
            machine[cmd->parameter.registers[0]] +=
                machine[cmd->parameter.registers[1]];
            break;
        case SUB:
            machine[cmd->parameter.registers[0]] -=
                machine[cmd->parameter.registers[1]];
            break;
        case MUL:
            machine[cmd->parameter.registers[0]] *=
                machine[cmd->parameter.registers[1]];
            break;
        case DIV:
            machine[cmd->parameter.registers[0]] /=
                machine[cmd->parameter.registers[1]];
            break;
        case OUT:
            printf("%d\n", machine[cmd->parameter.registers[1]]);
            break;
        case IN:
            res = scanf("%d", &tmp_in);
            if (res != 1)
            {
                fprintf(stderr, "Error in IN input\n");
                return 1;
            }
            machine[cmd->parameter.registers[1]] = (unsigned char)tmp_in;
            break;
        default:
            break;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    FILE *f;
    unsigned code;
    struct mnemo_t cmd;
    unsigned char machine[4] = {0};

    if (argc < 2)
    {
        fprintf(stderr, "No program at argv[1]");
        abort();
    }

    if ((f = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "Error opening file %s\n", argv[1]);
        return 1;
    }

    while (fscanf(f,"%x", &code) == 1)
    {
        cmd = decode(code);

        if (cmd.command == ERROR)
        {
            fprintf(stderr, "Error decoding program\n");
            fclose(f);
            abort();
        }
        
        execute(&cmd, machine);
    }
    fclose(f);
}