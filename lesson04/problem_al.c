#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#ifdef NDEBUG
struct node_t
{
    struct node_t *next;
    int data;
};
#endif

// считывает список из входного файла, так, чтобы все чётные числа были в начале
struct node_t *read_list(FILE *inp)
{
    struct node_t *list = NULL;
    struct node_t *even = NULL, *eventop = NULL;
    struct node_t *odd = NULL, *oddtop = NULL;   

    for (; ; )
    {
        int res, num;
        struct node_t *node;

        res = fscanf(inp, "%d", &num);

        if (res == EOF)
            break;

        if (res != 1)
        {
            fprintf(stderr, "File have broken format\n");
            fclose(inp);
            abort();
        }

        node = calloc(1, sizeof(struct node_t));
        node->data = num;

        if (num & 0x1)
        {
            if (odd)
                odd->next = node;
            else
                oddtop = node;

            odd = node;
        }
        else
        {
            if (even)
                even->next = node;
            else
                eventop = node;

            even = node;
        }
    }

    if (even)
    {
        even->next = oddtop;
        list = eventop;
    }
    else
        list = oddtop;

    return list;
}

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

#ifdef NDEBUG 

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
    FILE *f;
    struct node_t *list;

    f = fopen("1.txt", "r");
    if (f == NULL)
    {
        perror("Cannot open <1.txt>");
        abort();
    }
    
    list = read_list(f);
    
    fclose(f);
    
    print_list(list);

    delete_list(list);
}

#endif