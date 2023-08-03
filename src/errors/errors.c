#include "errors.h"

Error *createError(int code, int line, int col, char *message)
{
    Error *error = (Error *)malloc(sizeof(Error));

    error->code = code;
    error->line = line;
    error->col = col;
    error->message = message;

    return error;
}

void addError(Error *base, Error *error)
{
    Error *tmp = base;
    while(tmp->next)
        tmp = tmp->next;

    tmp->next = error;
}

int printError(Error *error)
{
    return printf("\033[31mLexer Error (%06d:%03d):\n\tCode %d\n\t%s\033[0m\n", error->line, error->col, error->code, error->message);
}

void listErrors(Error *error)
{
    Error *tmp = error;

    while(tmp)
    {
        printError(tmp);
        tmp = tmp->next;
    }
}
