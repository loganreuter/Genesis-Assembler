#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "asm.h"

int Read(char *filepath){
    debug("Read", "%s", filepath);
    FILE *file;

    /*
    Open the file
    Report error if it occurs
    */
    file = fopen(filepath, "r");
    if(!file)
    {
        perror(filepath);
        return EXIT_FAILURE;
    }

    Lexer *lexer = Tokenize(file);

    return 0;
}