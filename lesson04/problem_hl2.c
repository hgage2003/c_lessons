/*
    Problem HL2 — длина петли в списке
    Заранее задан (определять его не надо) тип структуры

    struct node_t {
    struct node_t *next;
    int data;
    };
    Вам необходимо написать функцию с заранее заданной сигнатурой

    // определяет длину петли в односвязном списке
    // возвращает длину если есть, 0 если петли нет
    int loop_len(struct node_t *top);
    Если петля есть, она должна возвращать её длину, если нет -- ноль

    В посылке должна быть только указанная функция, отправлять функцию main не нужно


    Пример 1

    Входной список: 2 → 4 → 6 → 1

    Выход: 0


    Пример 2

    Входной список: 2 → 4 → 6 → 2 → 4 → 6 → ...

    Выход: 3


    Пример 3

    Входной список: 2 → 4 → 6 → 4 → 6 → ...

    Выход: 2


    Пример 4

    Входной список: 2 → 4 → 6 → 6 → 6 → ...

    Выход: 1
*/

#ifdef NDEBUG
#include <stdio.h>
#include <stdlib.h>

struct node_t {
  struct node_t *next;
  int data;
};
#endif

#include <assert.h>

// определяет длину петли в односвязном списке
// возвращает длину если есть, 0 если петли нет
int loop_len(struct node_t *top)
{
    struct node_t *r, *t;
    int steps = 1; // заяц скачет степени двойки шагов
    int looplen = 0;
    
    if (!top || !top->next)
        return 0;

    r = t = top;
    for(; ; )
    {
        steps *= 2;
        for (int i = 0; i < steps; ++i)
        {
            r = r->next;
            ++looplen;
            if (!r)
                return 0;
            if (r == t)
                return looplen;
        }

        // телепорт черепахи
        t = r;
        looplen = 0;
    }

    assert(0);
}

#ifdef NDEBUG
// crashes on loop
void free_list(struct node_t *list)
{
    while (list)
    {
        struct node_t *tmp = list->next;
        free(list);
        list = tmp;
    }
}

// печатает до 20 эл-тов списка
void print_list20(const struct node_t *list)
{
    for (int i = 0; i < 20; ++i)
    {
        if (!list)
            break;

        printf("%d ", list->data);
        list = list->next;      
    }
    printf("\n");
}

int main()
{
    struct node_t *testlist = NULL;

    int arr[] = {2, 4, 6, 1};
    struct node_t* node, *iter;

    for (int i = 0; i < sizeof(arr) / sizeof(int); ++i)
    {
        node = calloc(1, sizeof(struct node_t));
        node->data = arr[i];
       
        if (!i)
        {
            testlist = iter = node;
            continue;
        }

        iter->next = node;
        iter = node;
    }

    print_list20(testlist);

    printf("list_is_a_loop(noloop) == %d\n", loop_len(testlist));

    iter->next = testlist->next;
    print_list20(testlist);
    printf("list_is_a_loop(loop) == %d\n", loop_len(testlist));

    iter->next = NULL;
    free_list(testlist);
}
#endif