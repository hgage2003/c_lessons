/*
    Problem SPO — iterative preorder
    Ваша задача — написать функцию, которая:

    Принимает указатель на вершину дерева.

    Печатает на stdout её preorder обход.

    Функция должна быть итеративной и использовать явный стек.

    void print_pre(struct tree_t *top) {
    // TODO: ваш код здесь
    }
    Считайте, что дерево задано следующей структурой

    struct tree_t {
    struct tree_t *left;
    struct tree_t *right;
    int data;
    };
    Изначально дерево задано в формате: количество вершин + топология + данные, где топология это
    правильное скобочное выражение, но код считывания, реконструкции и освобождения дерева уже
    написан за вас

    Отправка должна состоять только из указанной функции (и сколько угодно вспомогательных). Писать
    всю программу с функцией main не надо
*/

#ifdef NDEBUG
#include <stdio.h>
#include <malloc.h>

struct tree_t
{
    struct tree_t *left;
    struct tree_t *right;
    int data;
};
#endif

#include <assert.h>

struct stacknode
{
    struct stacknode *next;
    struct tree_t *data;
};

void push(struct stacknode **stack, struct tree_t *data)
{
    struct stacknode *tmp;
    assert(stack);
        
    if (!data)
        return;

    tmp = calloc(1, sizeof(struct stacknode));
    tmp->data = data;
    tmp->next = *stack;
   
    *stack = tmp;
}

struct tree_t* pop(struct stacknode **stack)
{
    assert(stack);
    assert(*stack);

    struct tree_t *ret = (*stack)->data;
    struct stacknode *next = (*stack)->next;
    free(*stack);
    *stack = next;
    return ret;
}

void print_pre(struct tree_t *top)
{
    struct stacknode *stack = NULL;
    push(&stack, top);

    while(stack)
    {
        struct tree_t *tmp = pop(&stack);
        printf("%d ", tmp->data);
        push(&stack, tmp->right);
        push(&stack, tmp->left);
    }
}

#ifdef NDEBUG
void free_pre(struct tree_t *top)
{
    struct stacknode *stack = NULL;
    push(&stack, top);

    while(stack)
    {
        struct tree_t *tmp = pop(&stack);
        push(&stack, tmp->right);
        push(&stack, tmp->left);
        free(tmp);
    }
}

int main()
{
    struct tree_t *tmp, *top = NULL;

    tmp = calloc(1, sizeof(struct tree_t));
    tmp->data = 4;
    top = tmp;

    tmp = calloc(1, sizeof(struct tree_t));
    tmp->data = 2;
    top->left = tmp;

    tmp = calloc(1, sizeof(struct tree_t));
    tmp->data = 1;
    top->left->left = tmp;

    tmp = calloc(1, sizeof(struct tree_t));
    tmp->data = 9;
    top->right = tmp;

    tmp = calloc(1, sizeof(struct tree_t));
    tmp->data = 6;
    top->right->left = tmp;

    tmp = calloc(1, sizeof(struct tree_t));
    tmp->data = 10;
    top->right->right = tmp;

    tmp = calloc(1, sizeof(struct tree_t));
    tmp->data = 5;
    top->right->left->left = tmp;

    tmp = calloc(1, sizeof(struct tree_t));
    tmp->data = 8;
    top->right->left->right = tmp;

    print_pre(top);
    free_pre(top);
}
#endif