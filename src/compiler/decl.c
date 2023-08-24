#include "tokens.h"
#include "statement.h"
#include "symbol.h"
#include "gen.h"
#include "data.h"

// Parse the declaration of a variable
void var_declaration()
{

  // Ensure we have an 'int' token followed by an identifier
  // and a semicolon. Text now has the identifier's name.
  // Add it as a known identifier
    match_token(T_INT, "int");
    match_ident();
    add_glob(Text);
    gen_glob_symbol(Text);
    match_semi();
}
