#include "tokens.h"
#include "expr.h"
#include "tree.h"
#include "gen.h"
#include "cg.h"
#include "data.h"
#include "statement.h"
#include "scan.h"

// Parse one or more statements
void statements()
{
    struct AST_Node* tree;
    int reg;

    while (1) 
    {
        // Match a 'print' as the first token
        match_token(T_PRINT, "print");

        // Parse the following expression and
        // generate the assembly code
        tree = binary_expr(0);
        reg = gen_ast(tree);
        gen_print_int(reg);
        gen_free_regs();

        // Match the following semicolon
        // and stop if we are at EOF
        match_semi();
        if (Token.token == T_EOF)
        {
            return;
        }
    }
}

void match_token(int t, char* what)
{
    if (Token.token == t)
    {
        scan(&Token);
    } 
    else 
    {
        printf("%s expected on line %d\n", what, Line);
        exit(1);
    }
}

// Match a semicon and fetch the next token
void match_semi() 
{
    match_token(T_SEMI, ";");
}
