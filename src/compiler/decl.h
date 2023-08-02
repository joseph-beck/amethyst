int scan(struct token *t);

struct AST_Node* make_ast_node(int operation, struct AST_Node* left, struct AST_Node* right, int int_value);

struct AST_Node* make_ast_leaf(int operation, int int_value);

struct AST_Node* make_ast_unary(int operation, struct AST_Node *left, int int_value);

struct AST_Node* bin_expr(void);

int interpret_AST(struct AST_Node* n);
