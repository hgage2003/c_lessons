#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <limits.h>

struct uchar_array
{
    unsigned char *data;
    unsigned int size; 
};

void free_array(struct uchar_array* parr)
{
    assert(parr != 0);
    free(parr->data);
    parr->size = 0;
}

void read_input(struct uchar_array* parr, unsigned int* bit)
{
    int ninput;

    ninput = scanf("%ud", &parr->size);
    if ((ninput != 1) || (parr->size == 0))
    {
        printf("Error: wrong input\n");
        abort();
    }
    
    parr->data = calloc(parr->size, sizeof(unsigned char));
    if (parr->data == 0)
    {
        printf("Error: malloc error\n");
        abort;
    }

    for (int i = 0; i < parr->size; ++i)
    {
        ninput = scanf("%hhu", &(parr->data[i]));
        if (ninput != 1)
        {
            printf("Error: wrong input\n");
            free_array(parr);
            abort();
        }
    }

    ninput = scanf("%u", bit);
    if (ninput != 1)
    {
        printf("Error: wrong input\n");
        abort();
    }
}

int main()
{
    struct uchar_array arr;
    unsigned int bit, byte;

    read_input(&arr, &bit);

    byte = bit / CHAR_BIT;
    bit %= CHAR_BIT;
    
    if (byte < arr.size)
        arr.data[byte] ^= (1 << bit);
    
    for (int i = 0; i < arr.size; ++i)
        printf("%u ", arr.data[i]);
    printf("\n");

    free_array(&arr);
}