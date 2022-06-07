// htab_lookup_add.c
// Řešení IJC-DU2, příklad 2, 18.4.2022
// Autor: Nikita Kotvitskiy (xkotvi01), FIT
// Přeloženo: gcc 9.4.0

#include "htab.h"
#include "htab_private_header.h"
#include <stdlib.h>

htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key)
{
    //Try to find item
    htab_pair_t * ret = htab_find(t, key);
    if (ret != NULL)
        return ret;

    //If the item is not in the table, calculate its bucket and add item to start of bucket
    htab_arr_size_t bucket = htab_hash_function(key) % t->arr_size;
    struct htab_item * new_item = malloc(sizeof(struct htab_item));
    if (new_item == NULL)
        return NULL;
    new_item->next = t->arr_ptr[bucket];
    char * str = malloc(strlen(key));
    strcpy(str, key);
    new_item->pair.key = str;
    t->arr_ptr[bucket] = new_item;
    t->size++;

    //Prepare return value and check if we need to resize the table. If yes, return value will be changed due to new position of the item in table
    ret = &(new_item->pair);
    if ((t->size) / (t->arr_size) > AVG_LEN_MAX)
    {
        htab_resize(t, (t->arr_size) * 2);
        ret = htab_find(t, key);
    }

    return ret;
}