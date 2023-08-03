#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "lexer.h"

const int BUFFER_SIZE = 10;

const char *keywords[] = {
    "BYTE",
    "WORD",
    "DWORD",
    "section",
    "global",
    "EOF"
};

const char *instructions[] = {
    "mov",
    "str",
    "add",
    "iadd",
    "incr",
    "sub",
    "isub",
    "decr",
    "mul",
    "imul",
    "div",
    "idiv",
    "mod",
    "imod",
    "EOF"
};

int isBlankLine(char *line)
{
    for (int i = 0; i < strlen(line); i++)
    {
        if (!isspace(line[i]))
            return 0;
    }
    return 1;
}

int removeComments(char *line)
{
    char *ptr = strchr(line, ';');
    if (ptr != NULL)
        *ptr = '\0';
    return 0;
    return 1;
}

int isKeyword(char *token)
{
    int i = 0;
    while(strcmp(keywords[i], "EOF"))
    {
        if(!strcmp(token, keywords[i]))
            return 1;
        i++;
    }
    return 0;
}

int isInstr(char *token)
{
    int i = 0;
    while(strcmp(instructions[i], "EOF"))
    {
        if(!strcmp(token, instructions[i]))
            return 1;
        i++;
    }
    return 0;
}

char peak(Lexer *lexer)
{
    return lexer->line[lexer->col];
}

char next(Lexer *lexer)
{
    return lexer->line[lexer->col++];
}

void addRegister(Lexer *lexer)
{
    Token *t = (Token *)malloc(sizeof(Token));
    t->type = REGISTER;
    t->line = lexer->line_cnt;
    t->col = lexer->col;
    t->next = NULL;

    char *raw = (char *)malloc(BUFFER_SIZE * sizeof(char)); 
    char *line = lexer->line;
    lexer->col++;

    int i = 0;
    raw[i++] = '%';
    while(isalpha(peak(lexer)))
    {        
        if(i >= BUFFER_SIZE)
            break;
        raw[i++] = next(lexer);
    }
    raw[i] = '\0';

    t->raw = raw;
    t->value = raw + 1;

    addToken(lexer, t);
}

void addSection(Lexer *lexer)
{
    Token *t = (Token *)malloc(sizeof(Token));
    t->type = SECTION;
    t->line = lexer->line_cnt;
    t->col = lexer->col;
    t->next = NULL;

    char *raw = (char *)malloc(BUFFER_SIZE * sizeof(char));
    char *line = lexer->line;
    lexer->col++;

    int i = 0;
    raw[i++] = '.';
    while (isalpha(peak(lexer)))
    {
        if (i >= BUFFER_SIZE)
            break;
        raw[i++] = next(lexer);
    }
    raw[i] = '\0';

    t->raw = raw;
    t->value = raw + 1;
    printf("%s %s\n", t->raw, t->value);

    addToken(lexer, t);
}

char *getStr(Lexer *lexer)
{
    char *buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));

    int i = 0;
    int size = BUFFER_SIZE;
    while (isalpha(peak(lexer)) || peak(lexer) == '_')
    {
        if (i >= size)
        {
            size += BUFFER_SIZE;
            buffer = (char *)realloc(buffer, size * sizeof(char));
        }

        buffer[i++] = next(lexer);
    }
    buffer[i] = '\0';

    return buffer;
}

/// @brief Creates a lexer with tokens for a given input file.
/// @param file 
/// @return Pointer to a Lexer struct
Lexer *Tokenize(FILE *file)
{
    Lexer *lexer = (Lexer *)malloc(sizeof(Lexer));
    char line[MAX_LINE_LENGTH] = {0};
    lexer->line_cnt = 0;
    lexer->num_tokens = 0;
    lexer->tokens = NULL;
    lexer->errors = NULL;

    while (fgets(line, MAX_LINE_LENGTH, file))
    {
        // Skip lines that are just comments or are empty
        if (line[0] == ';' || isBlankLine(line))
            continue;

        removeComments(line);

        lexer->col = 0;
        lexer->line = line;
        debug("tokenize", "line[%06d]: %s", ++lexer->line_cnt, lexer->line);

        while(line[lexer->col])
        {
            char c = line[lexer->col];
            if(c == '[')
            {
                addToken(lexer, createToken(LBRACK, "[", "[", lexer->line_cnt, lexer->col));
                lexer->col++;
            }
            else if(c == ']')
            {
                addToken(lexer, createToken(RBRACK, "]", "]", lexer->line_cnt, lexer->col));
                lexer->col++;
            }
            else if(c == ',')
            {
                addToken(lexer, createToken(COMMA, ",", ",", lexer->line_cnt, lexer->col));
                lexer->col++;
            }
            else if(c == '+')
            {
                addToken(lexer, createToken(PLUS, "+", "+", lexer->line_cnt, lexer->col));
                lexer->col++;
            }
            else if(c == '-')
            {
                addToken(lexer, createToken(MINUS, "-", "-", lexer->line_cnt, lexer->col));
                lexer->col++;
            }
            else if(c == ':')
            {
                addToken(lexer, createToken(COLON, ":", ":", lexer->line_cnt, lexer->col));
                lexer->col++;
            }
            else if(c == '%')
            {
                addRegister(lexer);
            }
            else if(c == '.')
            {
                addSection(lexer);
            }
            else if(isalpha(c) || c == '_')
            {
                int col = lexer->col;
                int line_cnt = lexer->line_cnt;

                char *str = getStr(lexer);
                
                if(isKeyword(str))
                    addToken(lexer, createToken(KEYWORD, str, str, line_cnt, col));
                else if (isInstr(str))
                    addToken(lexer, createToken(INSTRUCTION, str, str, line_cnt, col));
                else
                    addToken(lexer, createToken(IDENT, str, str, line_cnt, col));
            }
            else
            {
                lexer->col++;
            }
        }
    }

    printTokens(lexer->tokens);

    fclose(file);

    return lexer;
}