// io.c
// Řešení IJC-DU2, příklad 2, 19.4.2022
// Autor: Nikita Kotvitskiy (xkotvi01), FIT
// Přeloženo: gcc 9.4.0

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <ctype.h>

int read_word(char *s, int max, FILE *f)
{
    int c;
    int size = 0;
    char bool_is_started = 0;
    while ((c = fgetc(f)) != EOF)
    {
        if (!bool_is_started)
        {
            if (isspace(c))
                continue;
            s[size] = c;
            size++;
            bool_is_started = 1;
        }
        else
        {
            if (!isspace(c) && size < max)
            {
                s[size] = c;
                size++;
            }
            else if (isspace(c))
            {
                s[size] = '\0';
                return 0;
            }
        }
    }
    s[size] = '\0';
    if (strlen(s) == 0)
        return EOF;
    return 0;
}