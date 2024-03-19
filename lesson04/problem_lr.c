#ifdef NDEBUG
#include <stdio.h>
#include <malloc.h>

struct node_t {
  struct node_t *next;
  int data;
};
#endif

struct node_t * reverse(struct node_t *top)
{
    struct node_t *fst = NULL, *snd = top, *temp;
    if (NULL == top) return NULL;
    if (NULL == top->next) return top;

    while (snd)
    {
        temp = snd->next;
        snd->next = fst;
        fst = snd;
        snd = temp;
    }

    return fst;
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
    struct node_t *testlist = NULL;

    int arr[] = {2, 4, 6, 1, 3, 15, 8, 21};
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

    print_list(testlist);
    testlist = reverse(testlist);
    print_list(testlist);
    
    delete_list(testlist);
}
#endif