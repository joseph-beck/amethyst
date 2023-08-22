#pragma once

#ifndef extern_
 #define extern_ extern
#endif

#include "tokens.h"

#include <stdio.h>

extern_ int             Line;
extern_ int	            Putback;
extern_ FILE*           Infile;
extern_ FILE*           Outfile;
extern_ struct token	Token;
extern_ char Text[TEXTLEN + 1];		// Last identifier scanned
