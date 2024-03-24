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

void print_pre(struct tree_t *top)
{
    if (!top)
        return;

    printf("%d ", top->data);
    print_pre(top->left);
    print_pre(top->right);
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

    print_pre(top);
    free_pre(top);
}
#endif