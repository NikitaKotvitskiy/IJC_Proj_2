// htab_resize.c
// Řešení IJC-DU2, příklad 2, 18.4.2022
// Autor: Nikita Kotvitskiy (xkotvi01), FIT
// Přeloženo: gcc 9.4.0

#include "htab.h"
#include "htab_private_header.h"
#include <stdlib.h>
#include "error.h"

void htab_resize(htab_t *t, size_t newn)
{
    //Allocate new pointer array of new size
    struct htab_item ** new_arr_ptr = calloc(sizeof(struct htab_item *), newn);
    if (new_arr_ptr == NULL)
        error_exit("htab pointer array allocation failure in function: %s\n", __func__);

    //Calculate new bucket for each item in old table and move them to the start of the bucket
    struct htab_item * current_item = t->arr_ptr[0];
    htab_arr_size_t current_bucket = 0; 
    for (int i = 0; i < t->size; i++)
    {
        while (current_item == NULL)
        {
            current_bucket++;
            current_item = t->arr_ptr[current_bucket];
        }
        htab_arr_size_t bucket = htab_hash_function(current_item->pair.key) % newn;
        struct htab_item *tmp = new_arr_ptr[bucket];
        new_arr_ptr[bucket] = current_item;
        current_item = current_item->next;
        new_arr_ptr[bucket]->next = tmp;
    }

    //Replacing the old pointer array with the new one and deallocating the old array
    free(t->arr_ptr);
    t->arr_size = newn;
    t->arr_ptr = new_arr_ptr;
}