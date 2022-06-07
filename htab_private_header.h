// htab_private_header.h
// Řešení IJC-DU2, příklad 2, 18.4.2022
// Autor: Nikita Kotvitskiy (xkotvi01), FIT
// Přeloženo: gcc 9.4.0

#ifndef __HTAB_PRIVATE_H__
#define __HTAB_PRIVATE_H__

#include "htab.h"
#define AVG_LEN_MIN 2
#define AVG_LEN_MAX 3

typedef int htab_size_t;
typedef int htab_arr_size_t;

struct htab_item
{
    htab_pair_t         pair;
    struct htab_item *  next;
};
struct htab
{
    htab_size_t          size;
    htab_arr_size_t      arr_size;
    struct htab_item **  arr_ptr;
};

#endif