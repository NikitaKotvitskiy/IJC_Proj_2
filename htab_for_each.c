// htab_for_each.c
// Řešení IJC-DU2, příklad 2, 18.4.2022
// Autor: Nikita Kotvitskiy (xkotvi01), FIT
// Přeloženo: gcc 9.4.0

#include "htab.h"
#include "htab_private_header.h"

//Take each element of the table and send its data to f function
void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data))
{
    struct htab_item * current_item = t->arr_ptr[0];
    htab_arr_size_t current_bucket = 0; 
    for (int i = 0; i < t->size; i++)
    {
        while (current_item == NULL)
        {
            current_bucket++;
            if (current_bucket == t->arr_size)
                return;
            current_item = t->arr_ptr[current_bucket];
        }
        f(&(current_item->pair));
        current_item = current_item->next;
    }
}