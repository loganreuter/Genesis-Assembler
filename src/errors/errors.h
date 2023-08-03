#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>

typedef struct Error Error;

struct Error
{
    int code;
    int line;
    int col;
    char *message;
    Error *next;
};

Error *createError(int value, int line, int col, char *message);

void addError(Error *base, Error *error);

int printError(Error *error);

void listErrors(Error *error);

#endif