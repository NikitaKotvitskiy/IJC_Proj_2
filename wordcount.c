// wordcount.c
// Řešení IJC-DU2, příklad 2, 18.4.2022
// Autor: Nikita Kotvitskiy (xkotvi01), FIT
// Přeloženo: gcc 9.4.0

#include <string.h>
#include <stdio.h>
#include "htab.h"
#include "error.h"
#include <stdlib.h>

#define WORD_LIMIT 127
int read_word(char *s, int max, FILE *f);

void print_pair(htab_pair_t * data)
{
    printf("%s\t%d\n", data->key, data->value);
}

int main()
{
    htab_t * m = htab_init(0);
    if (m == NULL)
        error_exit("htab allocation failure\n");
    char * word = malloc(WORD_LIMIT);
    while (read_word(word, WORD_LIMIT, stdin) != EOF)
        htab_lookup_add(m, word)->value++;
    htab_for_each(m, &print_pair);

    free(word);
    htab_free(m);
}