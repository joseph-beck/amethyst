#pragma once

int gen_ast(struct AST_Node* n);

void gen_preamble();

void gen_postamble();

void gen_free_regs();

void gen_print_int(int reg);
