#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "asm.h"

#define MAX_LINE_LENGTH 100

int Read(char *filepath){
    debug("Read", "%s", filepath);
    FILE *file;
    char line[MAX_LINE_LENGTH] = {0};
    unsigned int line_count = 0;

    file = fopen(filepath, "r");
    if(!file)
    {
        perror(filepath);
        return EXIT_FAILURE;
    }
    
    while (fgets(line, MAX_LINE_LENGTH, file))
    {
        printf("line[%06d]: %s", ++line_count, line);
        
        if(line[strlen(line) - 1] != '\n')
            printf("\n");
    }

    return fclose(file);
}

int main(int argc, char* argv[]){
    printf("Hello, World\n");

    for(int i = 0; i < argc; i++){
        printf("%s\n", argv[i]);
    }
    if(argc < 1)
        return EXIT_FAILURE;
    char *path = argv[1];

    return Read(path);
}