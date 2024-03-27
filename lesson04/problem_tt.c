/*
    Problem TT — дерево из обходов
    Ваша задача — написать программу, которая:

    Принимает со stdin количество вершин, а потом preorder и inorder обходы дерева

    Печатает на stdout само дерево в обычном формате: количество вершин + топология + данные, где топология это правильное скобочное выражение из единиц и нулей


    Пример 1

    Вход: 5 4 3 1 0 2 1 3 4 2 0

    Означает: 5 вершин, preorder порядок 4 3 1 0 2, inorder 1 3 4 2 0

    Выход: 1 3 2 0 4
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>
#include <assert.h>

struct stacknode
{
    struct stacknode *next;
    struct tree_t *data;
};

struct tree_t
{
    struct tree_t *left;
    struct tree_t *right;
    int data;
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
    struct tree_t *ret = NULL;
    struct stacknode *next = NULL;

    assert(stack);
    assert(*stack);

    ret = (*stack)->data;
    next = (*stack)->next;
    free(*stack);
    *stack = next;
    return ret;
}

void free_tree(struct tree_t *top)
{
    if (!top)
        return;

    free_tree(top->left);
    free_tree(top->right);

    free(top);
}

void print_post(struct tree_t *top)
{
    if (!top)
        return;

    print_post(top->left);
    print_post(top->right);

    printf("%d ", top->data);    
}

int read_input(int** preorder, int **inorder)
{
    int ret, size = 0;

    ret = scanf("%d", &size);
    if (ret != 1)
    {
        fprintf(stderr, "Error: wrong input\n");
        abort();
    }

    *preorder = calloc(size, sizeof(int));
    if (!(*preorder))
    {
        fprintf(stderr, "Calloc error\n");
        abort();
    }

    for (int i = 0; i < size; ++i)
    {
        ret = scanf("%d", &((*preorder)[i]));
        if (ret != 1)
        {
            fprintf(stderr, "Error: wrong input\n");
            free(*preorder);
            abort();
        }
    }

    *inorder = calloc(size, sizeof(int));
    if (!(*inorder))
    {
        fprintf(stderr, "Calloc error\n");
        abort();
    }

    for (int i = 0; i < size; ++i)
    {
        ret = scanf("%d", &((*inorder)[i]));
        if (ret != 1)
        {
            fprintf(stderr, "Error: wrong input\n");
            free(*preorder);
            free(*inorder);
            abort();
        }
    }

    return size;
}

int find(int* array, int from, int to, int data)
{
    for (int i = from; i < to; ++i)
        if (array[i] == data)
            return i;

    return -1;
}

struct tree_t *make_node(int *preorder, int *num_pre, int size_pre, int *inorder, int min_in, int max_in)
{
    struct tree_t *node = NULL;
    int index = *num_pre, num_in;
    
    if (index >= size_pre)
        return node;
    
    num_in = find(inorder, min_in, max_in, preorder[index]);

    // есть ли нода
    if (num_in >= 0)
    { 
        node = calloc(1, sizeof(struct tree_t));
        
        if (!node)
        {
            fprintf(stderr, "Calloc Error");
            return node; // чтобы корректно удалилось то, что уже выделено
        }

        node->data = preorder[index++];
        node->left = make_node(preorder, &index, size_pre, inorder, min_in, num_in);
        node->right = make_node(preorder, &index, size_pre, inorder, num_in, max_in);
    }

    *num_pre = index;
    return node;
}

int main()
{
    struct tree_t *top = NULL;
    int *preorder, *inorder, size, num = 0;

    size = read_input(&preorder, &inorder);
    top = make_node(preorder, &num, size, inorder, 0, size);

    free(inorder);
    free(preorder);

    print_post(top);

    free_tree(top);
}