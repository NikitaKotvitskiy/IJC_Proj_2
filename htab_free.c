// htab_free.c
// Řešení IJC-DU2, příklad 2, 18.4.2022
// Autor: Nikita Kotvitskiy (xkotvi01), FIT
// Přeloženo: gcc 9.4.0

#include "htab.h"
#include "htab_private_header.h"
#include <stdlib.h>

void htab_free(htab_t * t)
{
    htab_clear(t);
    free(t->arr_ptr);
    free(t);
}