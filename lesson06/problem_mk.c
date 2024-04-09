/*
Problem MK — эмулятор
Регистровый файл состоит из четырёх восьмиразрядных регистров

Register file
Register            A	B	C	D
Encoding (binary)	00	01	10	11

Вам задана следующая система команд и таблица мнемоник

Instruction set

Mnemonic                                    Encoding (binary)
MOVI Imm — move constant to D register	    0IIIIIII
ADD R, R — add two registers modulo 256	    1000RRRR
SUB R, R — sub two registers modulo 256	    1001RRRR
MUL R, R — mul two registers modulo 256	    1010RRRR
DIV R, R — div two registers modulo 256	    1011RRRR
IN R — read register R from keyboard	    110000RR
OUT R — write register R to screen	        110001RR

Вам приходит имя файла закодированной программы как параметр argv[1] и стандартный ввод
на stdin

Вам необходимо симулировать работу программы и вывести всё что она выводит на stdout

Пример 1

Программа: 0x70 0xc7 0xc1 0x87 0x27 0xc5 0x8d 0xc1 0x87 0x6f 0xc5 0xc7

Вход:104 64

Выход:112
216
63
111

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

enum cmd_t {MOVI, ADD, SUB, MUL, DIV, IN, OUT, ERROR};

union param_t
{
    enum reg_t {A, B, C, D} r[2];
    unsigned char imm;
};

struct mnemo_t
{
    enum cmd_t cmd;
    union param_t par;
};

struct mnemo_t decode(unsigned char code)
{
    struct mnemo_t res;
    unsigned char ncmd = (code & 0xf0) >> 4;
    enum reg_t r1 = (code & 0xc) >> 2,
        r2 = code & 0x3;

    if (!(code & 0x80))
    {
        res.cmd = MOVI;
        res.par.imm = code;
        return res;
    }

    res.par.r[0] = r1;
    res.par.r[1] = r2;
    
    switch (ncmd)
    {
        case 0x8:
            res.cmd = ADD;
            break;
        case 0x9:
            res.cmd = SUB;
            break;
        case 0xa:
            res.cmd = MUL;
            break;
        case 0xb:
            res.cmd = DIV;
            break;
        case 0xc:
            if (r1 == 1)
                res.cmd = OUT;
            else if (r1 == 0)
                res.cmd = IN;
            else
                res.cmd = ERROR;
            break;
        default:
            res.cmd = ERROR;
            break;
    }

    return res;
}

int execute(const struct mnemo_t *cmd, unsigned char machine[4])
{
    int res;
    unsigned tmp_in;
    enum reg_t r1 = cmd->par.r[0],
        r2 = cmd->par.r[1];

    switch (cmd->cmd)
    {
        case MOVI:
            machine[D] = cmd->par.imm;
            break;
        case ADD:
            machine[r1] += machine[r2];
            break;
        case SUB:
            machine[r1] -= machine[r2];
            break;
        case MUL:
            machine[r1] *= machine[r2];
            break;
        case DIV:
            machine[r1] /= machine[r2];
            break;
        case OUT:
            printf("%d\n", machine[r2]);
            break;
        case IN:
            res = scanf("%d", &tmp_in);
            if (res != 1)
            {
                fprintf(stderr, "Error in IN input\n");
                return 1;
            }
            machine[r2] = (unsigned char)tmp_in;
            break;
        default:
            return 1;
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
        abort();
    }

    while (fscanf(f,"%x", &code) == 1)
    {
        cmd = decode(code);

        if (cmd.cmd == ERROR)
        {
            fprintf(stderr, "Error decoding program\n");
            fclose(f);
            abort();
        }
        
        if (execute(&cmd, machine))
        {
            fprintf(stderr, "Error executing program\n");
            fclose(f);
            abort();
        }
    }
    fclose(f);
}