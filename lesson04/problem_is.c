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
void free_pre(struct tree_t *top)
{
    if (!top)
        return;

    free_pre(top->left);
    free_pre(top->right);

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
    free_pre(top);
}
#endif