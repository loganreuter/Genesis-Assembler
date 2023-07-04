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

const char *keywords[] = {
    "BYTE",
    "WORD",
    "DWORD",
    "section",
    "global"
};

int Read(char *filepath);

Lexer* Tokenize(FILE *file);

void Parse(Token *tokens);

void Generate();

#endif