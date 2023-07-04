#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "asm.h"

#define MAX_LINE_LENGTH 100

int isBlankLine(char *line)
{
    for(int i = 0; i < strlen(line); i++)
    {
        if(!isspace(line[i]))
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

int Read(char *filepath){
    debug("Read", "%s", filepath);
    FILE *file;
    
    /*
    Open the file
    Report error if it occurs
    */
    file = fopen(filepath, "r");
    if(!file){
        perror(filepath);
        return EXIT_FAILURE;
    }

    Lexer *lexer = Tokenize(file);
    return 0;
}

Lexer* Tokenize(FILE *file)
{
    Lexer *lexer = malloc(sizeof(Lexer));
    char line[MAX_LINE_LENGTH] = {0};
    unsigned int line_count = 0;

    const char *delim = " , : ";

    while (fgets(line, MAX_LINE_LENGTH, file))
    {   
        //Skip lines that are just comments or are empty
        if(line[0] == ';' || isBlankLine(line))
            continue;

        removeComments(line);
        
        int col = 0;
        debug("tokenize", "line[%06d]: %s", ++line_count, line);

        //Split line at delimeters
        char *token = strtok(line, delim);

        //Loop through tokens
        while(token != NULL)
        {
            debug("tokenize", "Token: %s\n", token);
            

            
            
            
            token = strtok(NULL, delim);
        }

    }

    fclose(file);

    return lexer;
}

char next(char *line, int col)
{
    return line[col];
}

char peek(char *line, int col)
{
    return line[col];
}

int main(int argc, char* argv[])
{
    if(argc < 1)
        return EXIT_FAILURE;
    char *path = argv[1];

    return Read(path);
}