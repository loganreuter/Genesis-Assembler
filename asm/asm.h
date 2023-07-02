#ifndef ASM_H
#define ASM_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "../debug/debug.h"
#include "../src/genesis.h"

typedef enum TokenType {
    OPERATION,
    REGISTER,
    KEYWORD,

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
} Token;

int Read(char *filepath);

void Tokenize(FILE *file);

void Parse(Token *tokens);

void Generate();

#endif