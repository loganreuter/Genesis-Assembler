#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "../debug/debug.h"
#include "../src/genesis.h"

#include "regex.h"

#define MAX_LINE_LENGTH 100

typedef enum TokenType
{
    OPERATION,
    REGISTER,
    KEYWORD,
    IDENT,
    INT,
    FLOAT,
    HEX,

    COMMA,
    LBRACK,
    RBRACK,
    COLON,
    PERIOD,

    END,

    NUM_TYPES
} TokenType;

typedef struct Token
{
    TokenType type;
    char *value;
    char *raw_value;
    int line;
    int col;
} Token;

typedef struct Lexer
{
    Token *tokens;
} Lexer;

extern Lexer *Tokenize(FILE *file);

#endif