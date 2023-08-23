#pragma once

void freeall_registers(void);

void cg_preamble();

void cg_postamble();

int cg_load(int value);

int cg_add(int r1, int r2);

int cg_sub(int r1, int r2);

int cg_mul(int r1, int r2);

int cg_div(int r1, int r2);

void cg_print_int(int r);

int cg_store_glob(int r, char* identifier);

void cg_glob_symbol(char* sym);
