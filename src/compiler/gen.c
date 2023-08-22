#include "data.h"
#include "tokens.h"
#include "tree.h"
#include "scan.h"
#include "cg.h"

static int gen_ast(struct AST_Node* n) {
    int left_reg;
    int right_reg;

    // Get the left and right sub-tree values
    if (n->left)
    {
        left_reg = gen_ast(n->left);
    }
        
    if (n->right)
    {
        right_reg = gen_ast(n->right);
    }
        

    switch (n->operation) 
    {
    case A_ADD:
        return (cg_add(left_reg,right_reg));
    case A_SUBTRACT:
        return (cg_sub(left_reg,right_reg));
    case A_MULTIPLY:
        return (cg_mul(left_reg,right_reg));
    case A_DIVIDE:
        return (cg_div(left_reg,right_reg));
    case A_INTLIT:
        return (cg_load(n->int_value));
    default:
        fprintf(stderr, "Unknown AST operator %d\n", n->operation);
        exit(1);
    }
}

void generate_code(struct AST_Node* n) {
    int reg;

    cg_preamble();
    reg = gen_ast(n);
    cg_print_int(reg);
    cg_postamble();
}
