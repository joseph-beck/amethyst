#include "compiler/compiler.h"

// Initialise global variables
static void init()
{
    Line = 1;
    Putback = '\n';
}

// Print out a usage if started incorrectly
static void usage(char *prog)
{
    fprintf(stderr, "Usage: %s infile\n", prog);
    exit(1);
}

// Entry point, check arguments and print a usage.
// Open up the input file and call scanfile() to scan the tokens in it.
void main(int argc, char *argv[])
{
    struct AST_Node *n;

    if (argc != 2)
    {
        usage(argv[0]);
    }

    init();

    if ((Infile = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
        exit(1);
    }

     // Create the output file
    if ((Outfile = fopen("out.s", "w")) == NULL)
    {
        fprintf(stderr, "Unable to create out.s: %s\n", strerror(errno));
        exit(1);
    }

    scan(&Token);			// Get the first token from the input
    n = binary_expr(0);		// Parse the expression in the file
    printf("%d\n", interpret_ast(n));	// Calculate the final result
    
    generate_code(n);

    fclose(Outfile);
    exit(0);
}
