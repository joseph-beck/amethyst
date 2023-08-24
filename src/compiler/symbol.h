#pragma once

#define NSYMBOLS        1024	// Number of symbol table entries

struct symbol_table
{
    char* name;
};

int find_glob(char* s);

int add_glob(char* name);
