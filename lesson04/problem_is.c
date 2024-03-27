/*
    Problem IS — проверка поисковости
    Ваша задача — написать функцию, которая:

    Принимает указатель на вершину дерева

    Печатает 1 на stdout, если дерево поисковое и 0, если нет

    int check_is_bst(struct tree_t *top) {
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


    Пример 1

    Вход: 8 1 1 1 0 0 0 1 1 1 0 0 1 0 0 1 0 4 2 1 9 6 5 8 10

    Ответ: 1


    Пример 2

    Вход: 8 1 1 1 0 0 0 1 1 1 0 0 1 0 0 1 0 4 2 1 8 6 5 10 9

    Ответ: 0
*/

#ifdef NDEBUG
#include <stdio.h>
#include <malloc.h>
#include <limits.h>

struct tree_t
{
    struct tree_t *left;
    struct tree_t *right;
    int data;
};
#endif

#include <assert.h>

int check_is_bst_lim(struct tree_t *top, int min, int max)
{
    assert(top);

    if ((top->data < min) || (top->data > max))
        return 0;

    if (top->left)
        if (!check_is_bst_lim(top->left, min, top->data))
            return 0;
    
    if (top->right)
        if (!check_is_bst_lim(top->right, top->data, max))
            return 0;

    return 1;
}

int check_is_bst(struct tree_t *top) 
{
    return check_is_bst_lim(top, INT_MIN, INT_MAX);
}

#ifdef NDEBUG
void free_tree(struct tree_t *top)
{
    if (!top)
        return;

    free_tree(top->left);
    free_tree(top->right);

    free(top);
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

    printf("%d\n", check_is_bst(top));
    free_tree(top);
}
#endif