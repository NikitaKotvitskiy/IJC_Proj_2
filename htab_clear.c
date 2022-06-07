// htab_clear.c
// Řešení IJC-DU2, příklad 2, 18.4.2022
// Autor: Nikita Kotvitskiy (xkotvi01), FIT
// Přeloženo: gcc 9.4.0

#include "htab.h"
#include "htab_private_header.h"
#include <stdlib.h>

void htab_clear(htab_t * t)
{
    for (int i = 0; i < t->arr_size; i++)
    {
        struct htab_item * cur = t->arr_ptr[i];
        if (cur == NULL)
            continue;
        while (t->arr_ptr[i] != NULL)
        {
            t->arr_ptr[i] = cur->next;
            free((char *)cur->pair.key);
            struct htab_item * tmp = cur;
            cur = cur->next;
            free(tmp);
            t->size--;
        }
    }
}