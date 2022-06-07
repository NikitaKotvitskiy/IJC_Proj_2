// htab_erase.c
// Řešení IJC-DU2, příklad 2, 18.4.2022
// Autor: Nikita Kotvitskiy (xkotvi01), FIT
// Přeloženo: gcc 9.4.0

#include "htab.h"
#include "htab_private_header.h"
#include <stdbool.h>
#include <stdlib.h>

bool htab_erase(htab_t * t, htab_key_t key)
{
    //If there is no item with the key in the table, then the function returns false
    htab_pair_t * item_to_erase = htab_find(t, key);
    if (item_to_erase == NULL)
        return false;

    //Find the bucket in which the item with the key is
    htab_arr_size_t bucket = htab_hash_function(key) % t->arr_size;

    //Cur is pointer to the head pointer of the bucket
    struct htab_item ** cur = &(t->arr_ptr[bucket]);

    //If the first item of the bucket is the one we need to erase, we erase him. Else we check each item in bucket. 
    if (htab_hash_function((*cur)->pair.key) == htab_hash_function(item_to_erase->key))
    {
        struct htab_item * tmp = *cur;
        *cur = tmp->next;
        free((char *)tmp->pair.key);
        free(tmp);
    }
    else while (true)
    {
        if (htab_hash_function((*cur)->next->pair.key) == htab_hash_function(item_to_erase->key))
        {
            struct htab_item * tmp = (*cur)->next;
            (*cur)->next = tmp->next;
            free((char *)tmp->pair.key);
            free(tmp);
            break;
        }
        *cur = (*cur)->next;
    }
    t->size--;

    //Check average lenght of the table
    if ((t->size) / (t->arr_size) < AVG_LEN_MIN)    
        htab_resize(t, t->arr_size / 2);

    return true;
}