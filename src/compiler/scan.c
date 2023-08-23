#include "data.h"
#include "scan.h"
#include "tokens.h"

static int chr_pos(char* s, int c)
{
    char* p;
    p = strchr(s, c);
    return (p ? p - s : -1);
}

static int next(void)
{
    int c;

    if (Putback)
    {
        c = Putback;
        Putback = 0;
        return c;
    }

    c = fgetc(Infile);
    if ('\n' == c)
    {
        Line++;
    }

    return c;
}

static void putback(int c) {
    Putback = c;
}

static int skip() {
    int c;

    c = next();
    while (' ' == c || '\t' == c || '\n' == c || '\r' == c || '\f' == c)
    {
        c = next();
    }

    return c;
}

static int scan_int(int c)
{
    int k;
    int val = 0;

    while ((k = chr_pos("0123456789", c)) >= 0)
    {
        val = val * 10 + k;
        c = next();
    }

    putback(c);
    return val;
}

// Scan an identifier from the input file and
// store it in buf[]. Return the identifier's length
static int scan_ident(int c, char* buf, int lim)
{
    int i = 0;

    // Allow digits, alpha and underscores
    while (isalpha(c) || isdigit(c) || '_' == c)
    {
        // Error if we hit the identifier length limit,
        // else append to buf[] and get next character
        if (lim - 1 == i)
        {
            printf("identifier too long on line %d\n", Line);
            exit(1);
        }
        else if (i < lim - 1)
        {
            buf[i++] = c;
        }
        c = next();
    }
    // We hit a non-valid character, put it back.
    // NUL-terminate the buf[] and return the length
    putback(c);
    buf[i] = '\0';
    return (i);
}

// Given a word from the input, return the matching
// keyword token number or 0 if it's not a keyword.
// Switch on the first letter so that we don't have
// to waste time strcmp()ing against all the keywords.
static int keyword(char* s)
{
    switch (*s)
    {
    case 'p':
        if (!strcmp(s, "print"))
        {
            return (T_PRINT);
        }   
        break;
    }
    return (0);
}

int scan(struct token* t)
{
    int c;
    int token_type;
    c = skip();

    switch (c)
    {
    case EOF:
        t->token = T_EOF;
        return (0);
    case '+':
        t->token = T_PLUS;
        break;
    case '-':
        t->token = T_MINUS;
        break;
    case '*':
        t->token = T_STAR;
        break;
    case '/':
        t->token = T_SLASH;
        break;
    case ';':
        t->token = T_SEMI;
        break;
    case '=':
        t->token = T_EQUALS;
        break;
    default:
        // If it's a digit, scan the
        // literal integer value in
        if (isdigit(c))
        {
	        t->int_value = scan_int(c);
	        t->token = T_INTLIT;
	        break;
        } 
        else if (isalpha(c) || '_' == c) 
        {
	        // Read in a keyword or identifier
	        scan_ident(c, Text, TEXTLEN);

	        // If it's a recognised keyword, return that token
	        if (token_type = keyword(Text)) 
            {
	            t->token = token_type;
	            break;
	        }
	        // Not a recognised keyword, so an error for now
	        printf("Unrecognised symbol %s on line %d\n", Text, Line);
	        exit(1);
        }
        // The character isn't part of any recognised token, error
        printf("Unrecognised character %c on line %d\n", c, Line);
        exit(1);
    }

    return (1);
}
