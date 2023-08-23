#pragma once

int gen_ast(struct AST_Node* n, int reg);

void gen_preamble();

void gen_postamble();

void gen_free_regs();

void gen_print_int(int reg);

void gen_glob_symbol(char* s);
