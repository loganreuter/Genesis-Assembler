#include "../src/asm.h"

int main(int argc, char *argv[])
{
    if (argc < 1)
        return EXIT_FAILURE;
    char *path = argv[1];

    return Read(path);
}