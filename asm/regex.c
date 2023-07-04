#include "regex.h"

/*
Code From:
https://www.cs.princeton.edu/courses/archive/spr09/cos333/beautiful.html
*/

int match(char *regex, char *text)
{
    if(regex[0] == '^')
        return matchhere(regex+1, text);
    do {
        if(matchhere(regex, text))
            return 1;
    } while(*text++ != '\0');
    return 0;
}

int matchhere(char *regex, char *text)
{
    
}