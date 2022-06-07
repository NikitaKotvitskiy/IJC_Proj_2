// tail.c
// Řešení IJC-DU2, příklad 1, 13.4.2022
// Autor: Nikita Kotvitskiy (xkotvi01), FIT
// Přeloženo: gcc 9.4.0

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define LINE_LIMIT 4095
#define DEFAULT_LINE_COUNT 10
#define OPTIONS_ERROR "ERROR: Options are not valid\n"
#define LINE_COUNT_ERROR "ERROR: Line count is not valid\n"
#define FILE_OPEN_ERROR "ERROR: File cannot be opened\n"
#define ALLOCATION_ERROR "ERROR: Allocation or deallocation error\n"
#define CLOSE_ERROR "ERROR: File close failure\n"
#define NEW_LINE_OPTION "-n"

enum ErrorType { OPT, LC, FO, ALLOC, FC };
void myError(int errorType)
{
    switch (errorType)
    {
        case OPT:
            fprintf(stderr, OPTIONS_ERROR); 
            break;
        case LC:
            fprintf(stderr, LINE_COUNT_ERROR); 
            break;
        case FO:
            fprintf(stderr, FILE_OPEN_ERROR); 
            break;
        case ALLOC:
            fprintf(stderr, ALLOCATION_ERROR);
    }
    exit(1);
}

//This structure consists program settings, which can be set by options
typedef struct Settings
{
    int lineCount;
    FILE * source;
} Sets;

//This structure represents one line in the tail.
typedef struct Line
{
    struct Line * prev;
    struct Line * next;
    char * l;
} line;

//This structure represents the whole tail
typedef struct Tail
{
    line * start;
    line * end;
    int lineSize;
} tail;

//Allocate memory for one line and return to the one
line * lineCrt()
{
    line * newLine = malloc(sizeof(line));
    if (newLine == NULL)
        myError(ALLOC);
    newLine->l = malloc(LINE_LIMIT);
    if (newLine->l == NULL)
        myError(ALLOC);
    newLine->next = NULL;
    newLine->prev = NULL;
    return newLine;
}

//Deallocate memory of the line
void lineFree(line * lineToFree)
{
    free(lineToFree->l);
    free(lineToFree);
}

//Deallocate the whole tail
void tailFree(line * firstLineInTale)
{
    if (firstLineInTale->next != NULL)
        tailFree(firstLineInTale->next);
    lineFree(firstLineInTale);
}

//Just append new line to the tail if the number of lines is less than max line number,
//else delete the oldest line, shift remaining lines and append new one to the start.
int tailAppend(tail * t, Sets sets)
{
    line * newLine = lineCrt();
    char * nl = fgets(newLine->l, LINE_LIMIT, sets.source);
    if (nl == NULL)
    {
        lineFree(newLine);
        return 1;
    }
    if (t->lineSize == 0)
    {
        t->start = newLine;
        t->end = t->start;
        t->lineSize = 1;
    }
    else
    {
        line * tmp = t->start;
        t->start = newLine;
        t->start->next = tmp;
        tmp->prev = t->start;
        if (t->lineSize < sets.lineCount)
            (t->lineSize)++;
        else
        {
            tmp = t->end;
            t->end = tmp->prev;
            t->end->next = NULL;
            lineFree(tmp);
        }
    }
    return 0;
}

//Check options of the program and set settings
void optionsProcessing(Sets * sets, int argc, char * argv[])
{
    if (argc == 1)
        return;
    if (argc < 1 || argc > 4)
        myError(OPT);
    bool source = false;
    bool lineCount = false;
    int newLineCount = 0;

    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(NEW_LINE_OPTION, argv[i]))
        {
            if (lineCount || i + 1 == argc)
                myError(OPT);
            lineCount = true;
            i++;
            newLineCount = atoi(argv[i]);
            if (newLineCount < 1)
                myError(LC);
            sets->lineCount = newLineCount;
        }
        else
        {
            if (source)
                myError(OPT);
            sets->source = fopen(argv[i], "r");
            if (sets->source == NULL)
                myError(FO);
        }
    }
}

int main(int argc, char * argv[])
{
    Sets sets = { .lineCount = DEFAULT_LINE_COUNT, .source = stdin }; 
    optionsProcessing(&sets, argc, argv);
    
    tail t = { .end = NULL, .start = NULL, .lineSize = 0 };
    while(!tailAppend(&t, sets));
    line * cur = t.end;
    for (int i = 0; i < t.lineSize; i++)
    {
        printf("%s", cur->l);
        cur = cur->prev;
    }
    tailFree(t.start);
    if (sets.source != stdin)
    {
        if (fclose(sets.source) == EOF)
            myError(FC);
    }
}