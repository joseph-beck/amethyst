#include "data.h"
#include "tokens.h"
#include "tree.h"
#include "scan.h"

// Parse a primary factor and return an
// AST node representing it.
static struct AST_Node* primary(void)
{
    struct AST_Node* n;

    // For an INTLIT token, make a leaf AST node for it
    // and scan in the next token. Otherwise, report a syntax error
    // for any other token type.
    switch (Token.token)
    {
    case T_INTLIT:
        n = make_ast_leaf(A_INTLIT, Token.intvalue);
        scan(&Token);
        return n;
    default:
        fprintf(stderr, "syntax error on line %d\n", Line);
        exit(1);
    }
}

// Convert a token into an AST operation.
int arithmetic_op(int token)
{
    switch (token)
    {
    case T_PLUS:
        return A_ADD;
    case T_MINUS:
        return A_SUBTRACT;
    case T_STAR:
        return A_MULTIPLY;
    case T_SLASH:
        return A_DIVIDE;
    default:
        fprintf(stderr, "unknown token in arithmetic_op() on line %d\n", Line);
        exit(1);
    }
}

// Operator precedence for each token
static int op_prec[] = { 0, 10, 10, 20, 20, 0 };

// Check that we have a binary operator and
// return its precedence.
static int op_precedence(int token_type)
{
    int prec = op_prec[token_type];
    if (prec == 0) 
    {
        fprintf(stderr, "syntax error on line %d, token %d\n", Line, token_type);
        exit(1);
    }
    return prec;
}

struct AST_Node* binary_expr(int ptp)
{
    struct AST_Node* left;
    struct AST_Node* right;
    int token_type;

    // Get the integer literal on the left.
    // Fetch the next token at the same time.
    left = primary();

    // If no tokens left, return just the left node
    token_type = Token.token;
    if (token_type == T_EOF)
    {
        return left;
    }
        
    // While the precedence of this token is
    // more than that of the previous token precedence
    while (op_precedence(token_type) > ptp) {
        // Fetch the next token
        scan(&Token);

        // Recursively call binary_expr() with the
        // precedence of our token to build a sub-tree
        right = binary_expr(op_prec[token_type]);

        // Join that sub-tree with ours. Convert the token
        // into an AST operation at the same time.
        left = make_ast_node(arithmetic_op(token_type), left, right, 0);

        // Update the details of the current token.
        // If no tokens left, return just the left node
        token_type = Token.token;
        if (token_type == T_EOF)
        {
            return left;
        }   
    }

    // Return the tree we have when the precedence
    // is the same or lower
    return left;
}
