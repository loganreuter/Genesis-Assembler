#ifndef ASM_H
#define ASM_H

#include "stdio.h"
#include "stdlib.h"
#include <ctype.h>
#include "string.h"

#include "../debug/debug.h"
#include "../src/genesis.h"

#include "lexer.h"

int Read(char *filepath);

void Parse(Token *tokens);

void Generate();

#endif