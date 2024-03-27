/*
    Problem NO — натуральный порядок
    Ваша задача — написать программу, которая:

    Считывает поисковое дерево из файла как количество вершин + последовательность данных

    Выводит preorder обход дерева

    Отправка должна состоять из полной программы


    Пример 1

    Вход: 8 4 9 10 6 5 8 2 1

    Выход: 4 2 1 9 6 5 8 10


    Пример 2

    Вход: 10 8 4 3 7 5 2 0 6 1 9

    Выход: 8 4 3 2 0 1 7 5 6 9
*/

#include <stdio.h>
#include <malloc.h>
#include <assert.h>

struct tree_t
{
    struct tree_t *left;
    struct tree_t *right;
    int data;
};

void print_pre(struct tree_t *top)
{
    if (!top)
        return;

    printf("%d ", top->data);
    print_pre(top->left);
    print_pre(top->right);
}

void free_tree(struct tree_t *top)
{
    if (!top)
        return;

    free_tree(top->left);
    free_tree(top->right);

    free(top);
}

void insert_num(struct tree_t **tree, int num)
{
    struct tree_t **iter, *node;
    assert(tree);

    node = calloc(1, sizeof(struct tree_t));
    node->data = num;

    iter = tree;
    for (; ; )
    {
        if (!(*iter))
        {
            *iter = node;
            break;
        }

        if (num > (*iter)->data)
            iter = &((*iter)->right);
        else
            iter = &((*iter)->left);
    }
}

struct tree_t *read_input()
{
    int count, res;
    struct tree_t *top = NULL;

    res = scanf("%d", &count);
    if (res != 1)
    {
        fprintf(stderr, "Format error: count\n");
        return NULL;
    }

    for (int i = 0; i < count; ++i)
    {
        int node;
        res = scanf("%d", &node);
        if (res != 1)
        {
            fprintf(stderr, "Format error: node\n");
            free_tree(top);
            return NULL;
        }

        insert_num(&top, node);
    }

    return top;
}

int main()
{
    struct tree_t *top = NULL;

    top = read_input();

    print_pre(top);
    free_tree(top);
}