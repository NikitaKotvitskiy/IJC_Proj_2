// htab_bucket_count.c
// Řešení IJC-DU2, příklad 2, 18.4.2022
// Autor: Nikita Kotvitskiy (xkotvi01), FIT
// Přeloženo: gcc 9.4.0

#include "htab.h"
#include "htab_private_header.h"

size_t htab_bucket_count(const htab_t * t)
{
    return t->arr_size;
}