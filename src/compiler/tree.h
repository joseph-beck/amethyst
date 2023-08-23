#pragma once

#include <stdio.h>
#include <stdlib.h>

// Abstract Syntax Tree structure
struct AST_Node
{
  int operation;				        // "Operation" to be performed on this tree
  struct AST_Node* left;			    // Left child trees
  struct AST_Node* right;               // Right child trees
  union {
    int int_value;		// For A_INTLIT, the integer value
    int id;			// For A_IDENT, the symbol slot number
  } v;
};

// AST node types
enum
{
    A_ADD,
    A_SUBTRACT,
    A_MULTIPLY,
    A_DIVIDE,
    A_INTLIT,
    A_IDENT,
    A_LVIDENT,
    A_ASSIGN
};

struct AST_Node* make_ast_node(int operation, struct AST_Node* left, struct AST_Node* right, int int_value);

struct AST_Node* make_ast_leaf(int operation, int int_value);

struct AST_Node* make_ast_unary(int operation, struct AST_Node* left, int int_value);
