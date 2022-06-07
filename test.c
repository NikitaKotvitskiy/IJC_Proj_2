#include <stdio.h>
#include <stdlib.h>

int read_word(char *s, int max, FILE *f);

int main()
{
    char * word = malloc(128);
    while(read_word(word, 127, stdin) != EOF)
        printf("%s\n", word);
    free(word);
}