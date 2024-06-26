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

Вход: 104 64

Выход:
112
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

enum cmd_t {MOVI = 0, ADD = 8, SUB = 9, MUL = 10, DIV = 11, IN, OUT, CLAST, CERROR};
enum reg_t {A = 0, B, C, D, RLAST};

union operand_t
{
    struct {enum reg_t rd, rs;} ops; 
    enum reg_t rop;
    unsigned char imm;
};

struct instr_t
{
    enum cmd_t opcode;
    union operand_t opnd;
};

struct instr_t decode(unsigned char code)
{
    struct instr_t res;
    unsigned char ncmd = (code & 0xf0) >> 4;
    enum reg_t r1 = (code & 0xc) >> 2,
        r2 = code & 0x3;

    if (!(code & 0x80))
    {
        res.opcode = MOVI;
        res.opnd.imm = code;
        return res;
    }

    if ((code >> 6) & 0x1 == 1)
    {
        if ((code >> 2) == 0x30)
            res.opcode = IN;
        else if ((code >> 2) == 0x31)
            res.opcode = OUT;
        else
        {
            fprintf(stderr, "ERROR: bad inout\n");
            res.opcode = CERROR;
        }
        res.opnd.rop = r2;
        return res;
    }

    res.opnd.ops.rd = r1;
    res.opnd.ops.rs = r2;
    
    if (ncmd >= ADD && ncmd <= DIV)
        res.opcode = ncmd;
    else
    {
        fprintf(stderr, "ERROR: bad opcode\n");
            res.opcode = CERROR;
    }

    return res;
}

int execute(const struct instr_t *cmd, unsigned char machine[4])
{
    int res;
    unsigned tmp_in;
    enum reg_t rd = cmd->opnd.ops.rd,
        r2 = cmd->opnd.ops.rs, rop = cmd->opnd.rop;

    switch (cmd->opcode)
    {
        case MOVI:
            machine[D] = cmd->opnd.imm;
            break;
        case ADD:
            machine[rd] += machine[r2];
            break;
        case SUB:
            machine[rd] -= machine[r2];
            break;
        case MUL:
            machine[rd] *= machine[r2];
            break;
        case DIV:
            if (!machine[r2])
            {
                fprintf(stderr, "ERROR: divizion by zero\n");
                return 1;
            }
            machine[rd] /= machine[r2];
            break;
        case OUT:
            printf("%d\n", machine[rop]);
            break;
        case IN:
            res = scanf("%d", &tmp_in);
            if (res != 1)
            {
                fprintf(stderr, "ERROR: bad IN input\n");
                return 1;
            }
            machine[rop] = (unsigned char)tmp_in;
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
    struct instr_t cmd;
    unsigned char machine[4] = {0};

#if 1
    if (argc < 2)
    {
        fprintf(stderr, "ERROR: no program at argv[1]");
        abort();
    }

    if ((f = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "ERROR: can not open file %s\n", argv[1]);
        abort();
    }
#elif
    f = fopen("./prog1.enc", "r");
#endif

    while (fscanf(f,"%x", &code) == 1)
    {
        cmd = decode(code);

        if (cmd.opcode == CERROR)
        {
            fprintf(stderr, "ERROR: can not decode program\n");
            fclose(f);
            abort();
        }
        
        if (execute(&cmd, machine))
        {
            fprintf(stderr, "ERROR: can not execute program\n");
            fclose(f);
            abort();
        }
    }
    fclose(f);
}