#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TEXTLEN		512	// Length of symbols in input

// Token types
enum
{
    T_EOF,
    T_PLUS,
    T_MINUS,
    T_STAR,
    T_SLASH,
    T_INTLIT,
    T_SEMI,
    T_EQUALS,
    T_IDENT,
    // Keywords
    T_PRINT,
    T_INT
};

// Token structure
struct token
{
    int token;				    // Token type, from the enum list above
    int int_value;				// For T_INTLIT, the integer value
};

