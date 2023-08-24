#include "tokens.h"
#include "expr.h"
#include "tree.h"
#include "gen.h"
#include "cg.h"
#include "data.h"
#include "statement.h"
#include "scan.h"
#include "fatal.h"
#include "decl.h"

void print_statement()
{
    struct AST_Node* tree;
    int reg;

    // Match a 'print' as the first token
    match_token(T_PRINT, "print");

    // Parse the following expression and
    // generate the assembly code
    tree = binary_expr(0);
    reg = gen_ast(tree, -1);
    gen_print_int(reg);
    gen_free_regs();

    // Match the following semicolon
    match_semi();
}

void assignment_statement()
{
    struct AST_Node* left; 
    struct AST_Node* right; 
    struct AST_Node* tree;
    int id;

    // Ensure we have an identifier
    match_ident();

    // Check it's been defined then make a leaf node for it
    if ((id = find_glob(Text)) == -1)
    {
        fatals("Undeclared variable", Text);
    }
    right = make_ast_leaf(A_LVIDENT, id);

    // Ensure we have an equals sign
    match_token(T_EQUALS, "=");

    // Parse the following expression
    left = binary_expr(0);

    // Make an assignment AST tree
    tree = make_ast_node(A_ASSIGN, left, right, 0);

    // Generate the assembly code for the assignment
    gen_ast(tree, -1);
    gen_free_regs();

    // Match the following semicolon
    match_semi();
}


// Parse one or more statements
void statements()
{
    for ( ;; )
    {
        switch (Token.token)
        {
        case T_PRINT:
            print_statement();
            break;
        case T_INT:
            var_declaration();
            break;
        case T_IDENT:
            assignment_statement();
            break;
        case T_EOF:
            return;
        default:
            fatald("Syntax error, token", Token.token);
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
        fatals("Expected", what);
    }
}

// Match a semicon and fetch the next token
void match_semi() 
{
    match_token(T_SEMI, ";");
}

// Match an identifier and fetch the next token
void match_ident()
{
    match_token(T_IDENT, "identifier");
}
