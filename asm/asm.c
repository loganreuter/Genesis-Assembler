#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "asm.h"

#define MAX_LINE_LENGTH 100

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

    while (fgets(line, MAX_LINE_LENGTH, file))
    {   
        int col = 0;
        printf("line[%06d]: %s", ++line_count, line);
        
        while(1)
        {
            char c = next(line, col++);
            char *token_value;

            if(c == ';' || c == '\n' || c == '\r')
                break;
            
            if(c == '%')
            {
                char p = peek(line, col);
                while(p != ',')
                {
                    p = next(line, col++);
                    printf("P: %c\n", p);
                    // strcat(token_value, &p);
                    // printf("%s", token_value);
                    // p = peek(line, col);
                    
                    if(isspace(p) != 0)
                        printf("Hello");
                        break;
                }
                printf("Register: %s\n", token_value);
            }            
            // else if(isdigit(c))
            // {

            // }

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