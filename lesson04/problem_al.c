/*
    Problem AL — файл в список
    Заранее задан (определять его не надо) тип структуры

    struct node_t {
    struct node_t *next;
    int data;
    };
    Вам необходимо написать две функции с заранее заданными сигнатурами

    // считывает список из входного файла, так, чтобы все чётные числа были в начале
    struct node_t *read_list(FILE *inp);

    // удаляет список элемент за элементом
    void delete_list(struct node_t *top);
    Обратите внимание: все чётные числа должны быть строго в начале списка (а нечётные в конце) в том
    же порядке, в каком они идут в файле

    В посылке должны быть только указанные функции, отправлять функцию main не нужно


    Пример 1

    Входной файл: 1 2 3 4 5 6 7

    Выходной список: 2 → 4 → 6 → 1 → 3 → 5 → 7


    Пример 2

    Входной файл: пустой файл

    Выходной список: пустой список, результат read_list это NULL

    delete_list должна правильно обработать NULL как входной аргумент


    Пример 3

    Входной файл: 11 3 3 1 1 5 7 3 9 1

    Выходной список: 11 → 3 → 3 → 1 → 1 → 5 → ...
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#ifdef NDEBUG
struct node_t
{
    struct node_t *next;
    int data;
};
#endif

// считывает список из входного файла, так, чтобы все чётные числа были в начале
struct node_t *read_list(FILE *inp)
{
    struct node_t *list = NULL;
    struct node_t *even = NULL, *eventop = NULL;
    struct node_t *odd = NULL, *oddtop = NULL;   

    for (; ; )
    {
        int res, num;
        struct node_t *node;

        res = fscanf(inp, "%d", &num);

        if (res == EOF)
            break;

        if (res != 1)
        {
            fprintf(stderr, "File have broken format\n");
            fclose(inp);
            abort();
        }

        node = calloc(1, sizeof(struct node_t));
        node->data = num;

        if (num & 0x1)
        {
            if (odd)
                odd->next = node;
            else
                oddtop = node;

            odd = node;
        }
        else
        {
            if (even)
                even->next = node;
            else
                eventop = node;

            even = node;
        }
    }

    if (even)
    {
        even->next = oddtop;
        list = eventop;
    }
    else
        list = oddtop;

    return list;
}

#ifdef NDEBUG 
// удаляет список элемент за элементом
void delete_list(struct node_t *top)
{
    struct node_t *temp;
    while (top != NULL)
    {
        temp = top->next;
        free(top);
        top = temp;
    }
}

void print_list(const struct node_t *top)
{
    while (top != NULL)
    {
        if (top->next)
            printf("%d ", top->data);
        else
            printf("%d\n", top->data);

        top = top->next;
    }
}

int main()
{
    FILE *f;
    struct node_t *list;

    f = fopen("1.txt", "r");
    if (f == NULL)
    {
        perror("Cannot open <1.txt>");
        abort();
    }
    
    list = read_list(f);
    
    fclose(f);
    
    print_list(list);

    delete_list(list);
}

#endif