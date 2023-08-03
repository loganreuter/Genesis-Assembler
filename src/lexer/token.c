#include "lexer.h"

const char *getTokenType[NUM_TYPES] = {
    "INSTRUCTION",
    "REGISTER",
    "KEYWORD",
    "SECTION",
    "IDENT",
    "INT",
    "FLOAT",
    "HEX",

    "COMMA",
    "LBRACK",
    "RBRACK",
    "COLON",
    "PERIOD",
    "PLUS",
    "MINUS",

    "END",
};

Token *createToken(TokenType type, char *value, char *raw, int line, int col)
{
    Token *token = (Token *)malloc(sizeof(Token));
    token->type = type;
    token->value = value;
    token->raw = raw;
    token->line = line;
    token->col = col;
    token->next = NULL;

    return token;
}

int addToken(Lexer *lexer, Token *token)
{
    if(lexer->tokens == NULL)
    {
        lexer->tokens = token;
        return 0;
    }

    Token *tmp = lexer->tokens;

    while(tmp->next)
        tmp = tmp->next;
    
    tmp->next = token;
    
    return 0;
}

int _print(Token *token)
{
    return printf("(%6d:%3d) %-15s %s\n", token->line, token->col, getTokenType[token->type], token->value);
}

void printTokens(Token *token)
{
    Token *tmp = token;

    puts("Tokens:");
    while(tmp)
    {
        _print(tmp);
        tmp = tmp->next;
    }
}