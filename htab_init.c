// htab_init.c
// Řešení IJC-DU2, příklad 2, 18.4.2022
// Autor: Nikita Kotvitskiy (xkotvi01), FIT
// Přeloženo: gcc 9.4.0

#include "htab.h"
#include "htab_private_header.h"
#include <stdlib.h>

htab_t *htab_init(size_t n)
{
    if (n == 0)
        n = AVG_LEN_MIN;
    //Allocate memory for table structure
    htab_t *new_htab = malloc(sizeof(htab_t));
    if (new_htab == NULL)
        return NULL;
    new_htab->size = 0;
    //Allocate memory for pointer array
    new_htab->arr_ptr = calloc(sizeof(struct htab_item *), n);
    if (new_htab->arr_ptr == NULL)
        return NULL;
    new_htab->arr_size = n;
    return new_htab;
}