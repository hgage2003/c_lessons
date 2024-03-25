/*
    Problem LR — разворот списка
    Заранее задан (определять его не надо) тип структуры для односвязного списка

    struct node_t {
    struct node_t *next;
    int data;
    };
    Следующий код рекурсивно переворачивает список в памяти (вы можете быть уверены, что в списке
    нет петли)

    struct node_t * reverse(struct node_t *top) {
    struct node_t *xs;
    if (NULL == top) return NULL;
    if (NULL == top->next) return top;
    xs = reverse(top->next);
    top->next->next = top;
    top->next = NULL;
    return xs;
    }
    Вам необходимо написать и отправить на проверку такую же по смыслу функцию reverse, но
    работающую итеративно

    В посылке должна быть только указанная функция, отправлять функцию main не нужно


    Пример 1

    Входной список: 2 → 4 → 6 → 1

    Выходной список: 1 → 6 → 4 → 2
*/

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