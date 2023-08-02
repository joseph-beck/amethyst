#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Token types
enum
{
  T_EOF, T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INTLIT
};

// Token structure
struct token
{
  int token;				// Token type, from the enum list above
  int intvalue;				// For T_INTLIT, the integer value
};

// AST node types
enum
{
  A_ADD, A_SUBTRACT, A_MULTIPLY, A_DIVIDE, A_INTLIT
};

// Abstract Syntax Tree structure
struct AST_Node
{
  int operation;				        // "Operation" to be performed on this tree
  struct AST_Node* left;			    // Left child trees
  struct AST_Node* right;               // Right child trees
  int int_value;				        // For A_INTLIT, the integer value
};