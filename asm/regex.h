#ifndef REGEX_H
#define REGEX_H

int match(char *regex, char *text);

int matchhere(char *regex, char *text);

int matchstar(int c, char *regex, char *text);

#endif