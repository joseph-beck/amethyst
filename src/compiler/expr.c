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
    // and scan in the next token. Otherwise, a syntax error
    // for any other token type.
    switch (Token.token) {
      case T_INTLIT:
        n = make_ast_leaf(A_INTLIT, Token.intvalue);
        scan(&Token);
        return (n);
      default:
        fprintf(stderr, "syntax error on line %d\n", Line);
        exit(1);
    }
}


// Convert a token into an AST operation.
int arithmetic_op(int token)
{
    switch (token) {
        case T_PLUS:
            return (A_ADD);
        case T_MINUS:
            return (A_SUBTRACT);
        case T_STAR:
            return (A_MULTIPLY);
        case T_SLASH:
            return (A_DIVIDE);
        default:
            fprintf(stderr, "unknown token in arithmetic_op() on line %d\n", Line);
            exit(1);
    }
}


// Return an AST tree whose root is a binary operator
struct AST_Node* binary_expr(void)
{
    struct AST_Node* n;
    struct AST_Node* left;
    struct AST_Node* right;
    int node_type;

    // Get the integer literal on the left.
    // Fetch the next token at the same time.
    left = primary();

    // If no tokens left, return just the left node
    if (Token.token == T_EOF)
    {
        return (left);
    }

    // Convert the token into a node type
    node_type = arithmetic_op(Token.token);

    // Get the next token in
    scan(&Token);

    // Recursively get the right-hand tree
    right = binary_expr();

    // Now build a tree with both sub-trees
    n = make_ast_node(node_type, left, right, 0);
    return (n);
}
