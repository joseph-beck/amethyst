#include "data.h"
#include "tokens.h"
#include "tree.h"
#include "scan.h"
#include "cg.h"

int gen_ast(struct AST_Node* n, int reg)
{
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
        return (cg_add(left_reg, right_reg));
    case A_SUBTRACT:
        return (cg_sub(left_reg, right_reg));
    case A_MULTIPLY:
        return (cg_mul(left_reg, right_reg));
    case A_DIVIDE:
        return (cg_div(left_reg, right_reg));
    case A_INTLIT:
        return (cg_load(n->v.int_value));
    case A_IDENT:
        return (cg_load_glob(Gsym[n->v.id].name));
    case A_LVIDENT:
        return (cg_storg_lob(reg, Gsym[n->v.id].name));
    case A_ASSIGN:
        // The work has already been done, return the result
        return (right_reg);
    default:
        fprintf(stderr, "Unknown AST operator %d\n", n->operation);
        exit(1);
    }
}

void gen_preamble()
{
    cg_preamble();
}
void gen_postamble()
{
    cg_postamble();
}
void gen_free_regs()
{
    freeall_registers();
}
void gen_print_int(int reg)
{
    cg_print_int(reg);
}

void gen_glob_symbol(char* s)
{
    cg_glob_symbol(s);
}
