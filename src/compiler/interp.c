#include "tokens.h"
#include "tree.h"
#include "interp.h"

// List of AST operators
static char *AST_Operators[] = { "+", "-", "*", "/" };

// Given an AST, interpret the
// operators in it and return
// a final value.
int interpret_ast(struct AST_Node* n) {
    int left_val;
    int right_val;

    // Get the left and right sub-tree values
    if (n->left)
    {
      left_val = interpret_ast(n->left);
    }
    if (n->right)
    {
          right_val = interpret_ast(n->right);
    }

    // Debug: Print what we are about to do
    if (n->operation == A_INTLIT)
    {
        printf("int %d\n", n->int_value);
    }
    else
    {
        printf("%d %s %d\n", left_val, AST_Operators[n->operation], right_val);
    }

    switch (n->operation) {
        case A_ADD:
            return (left_val + right_val);
        case A_SUBTRACT:
            return (left_val - right_val);
        case A_MULTIPLY:
            return (left_val * right_val);
        case A_DIVIDE:
            return (left_val / right_val);
        case A_INTLIT:
            return (n->int_value);
        default:
            fprintf(stderr, "Unknown AST operator %d\n", n->operation);
            exit(1);
    }
}
