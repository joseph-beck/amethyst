#include "data.h"
#include "tree.h"

// Build and return a generic AST node
struct AST_Node* make_ast_node(
    int operation,
    struct AST_Node* left,
	struct AST_Node* right,
    int int_value)
{
    struct AST_Node* n;

    // Malloc a new ASTnode
    n = (struct AST_Node*) malloc(sizeof(struct AST_Node));
    if (n == NULL)
    {
        fprintf(stderr, "Unable to malloc in mkastnode()\n");
        exit(1);
    }

    // Copy in the field values and return it
    n->operator = operation;
    n->left = left;
    n->right = right;
    n->v.int_value = int_value;
    return (n);
}


// Make an AST leaf node
struct AST_Node* make_ast_leaf(int operation, int int_value)
{
  return (make_ast_node(operation, NULL, NULL, int_value));
}

// Make a unary AST node: only one child
struct AST_Node* make_ast_unary(
    int operation,
    struct AST_Node* left,
    int int_value)
{
    return (make_ast_node(operation, left, NULL, int_value));
}
