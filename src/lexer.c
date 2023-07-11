#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "lexer.h"

const char *keywords[] = {
    "BYTE",
    "WORD",
    "DWORD",
    "section",
    "global",
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
    while(strcmp(keywords[i], "EOF") == 0)
    {
        if(strcmp(token, keywords[i]) == 0)
            return 1;
        i++;
    }
    return 0;
}

/// @brief Creates a lexer with tokens for a given input file.
/// @param file 
/// @return Pointer to a Lexer struct
Lexer *Tokenize(FILE *file)
{
    Lexer *lexer = malloc(sizeof(Lexer));
    char line[MAX_LINE_LENGTH] = {0};
    unsigned int line_count = 0;

    const char *delim = " , : ";

    while (fgets(line, MAX_LINE_LENGTH, file))
    {
        // Skip lines that are just comments or are empty
        if (line[0] == ';' || isBlankLine(line))
            continue;

        removeComments(line);

        int col = 0;
        debug("tokenize", "line[%06d]: %s", ++line_count, line);

        // Split line at delimeters
        char *token = strtok(line, delim);

        // Loop through tokens
        while (token != NULL)
        {

            if(match("^%", token))
            {
                debug("tokenize", "Register: %s\n", token);
            }
            else if(isKeyword(token))
            {
                debug("tokenize", "Keyword: %s\n", token);
            }
            else { debug("tokenize", "Token: %s\n", token); }

            token = strtok(NULL, delim);
        }
    }

    fclose(file);

    return lexer;
}