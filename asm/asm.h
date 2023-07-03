#ifndef ASM_H
#define ASM_H

#include "stdio.h"
#include "stdlib.h"
#include <ctype.h>
#include "string.h"

#include "../debug/debug.h"
#include "../src/genesis.h"

typedef struct Error {
    char *step;
    char *message;
} Error;

typedef enum TokenType {
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

    NUM_TYPES
} TokenType;

typedef struct Token {
    TokenType type;
    char *value;
    char *raw_value;
    int line;
    int col;
} Token;

typedef struct Lexer {
    Token *tokens;
    Error *errors;
} Lexer;

int Read(char *filepath);

Lexer* Tokenize(FILE *file);

char next();
char peek(char *line, int col);


void Parse(Token *tokens);

void Generate();

#endif