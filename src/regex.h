#ifndef REGEX_H
#define REGEX_H

extern int match(char *regex, char *text);

extern int matchhere(char *regex, char *text);

extern int matchstar(int c, char *regex, char *text);

#endif