#ifdef NDEBUG
#include <stdio.h>
#include <stdlib.h>

struct node_t {
  struct node_t *next;
  int data;
};
#endif

// определяет есть ли петля в односвязном списке
// возвращает 0 если нет и 1 если есть
int list_is_a_loop(struct node_t *top)
{
    struct node_t *r, *t;
    int steps = 1; // заяц скачет степени двойки шагов
    
    if (!top || !top->next)
        return 0;

    r = t = top;
    for(; ; )
    {
        steps *= 2;
        for (int i = 0; i < steps; ++i)
        {
            r = r->next;
            if (!r)
                return 0;
            if (r == t)
                return 1;
        }

        // телепорт черепахи
        t = r;
    }

    return 0;
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

    printf("list_is_a_loop(noloop) == %d\n", list_is_a_loop(testlist));

    iter->next = testlist->next;
    print_list20(testlist);
    printf("list_is_a_loop(loop) == %d\n", list_is_a_loop(testlist));

    iter->next = NULL;
    free_list(testlist);
}
#endif