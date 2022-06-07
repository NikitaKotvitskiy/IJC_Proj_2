// htab_find.c
// Řešení IJC-DU2, příklad 2, 18.4.2022
// Autor: Nikita Kotvitskiy (xkotvi01), FIT
// Přeloženo: gcc 9.4.0

#include "htab.h"
#include "htab_private_header.h"

htab_pair_t * htab_find(htab_t * t, htab_key_t key)
{
    size_t key_hash = htab_hash_function(key);
    htab_arr_size_t bucket = key_hash % t->arr_size;
    struct htab_item * current = t->arr_ptr[bucket];
    while (true)
    {
        if (current == NULL)
            break;
        if (htab_hash_function(current->pair.key) == key_hash)
            return &(current->pair);
        current = current->next;
    }
    return NULL;
}