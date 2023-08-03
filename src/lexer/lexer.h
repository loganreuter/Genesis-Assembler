#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "../../include/Genesis/src/genesis.h"
#include "../../include/debug/debug.h"
#include "../errors/errors.h"

#define MAX_LINE_LENGTH 100

typedef struct Token Token;
typedef struct Lexer Lexer;

typedef enum TokenType
{
    INSTRUCTION,
    REGISTER,
    KEYWORD,
    SECTION,
    IDENT,
    INT,
    FLOAT,
    HEX,

    COMMA,
    LBRACK,
    RBRACK,
    COLON,
    PERIOD,
    PLUS,
    MINUS,

    END,

    NUM_TYPES
} TokenType;
const char *getTokenType[NUM_TYPES];

struct Token
{
    TokenType type;
    Token *next;
    char *value;
    char *raw;
    int line;
    int col;
};
Token *createToken(TokenType type, char *value, char *raw, int line, int col);
int addToken(Lexer *lexer, Token *token);
void printTokens(Token *token);

struct Lexer
{
    unsigned int line_cnt;
    unsigned int col;
    unsigned int num_tokens;
    Token *tokens;
    Error *errors;
    char *line;
};

Lexer *Tokenize(FILE *file);

#endif