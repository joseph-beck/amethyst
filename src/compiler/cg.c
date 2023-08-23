#include "data.h"
#include "tokens.h"
#include "tree.h"
#include "scan.h"

// List of available registers and their names
static int free_reg[4];
static char* reg_list[4] = { "%r8", "%r9", "%r10", "%r11" };

// Set all registers as available
void freeall_registers(void)
{
    free_reg[0] = free_reg[1] = free_reg[2] = free_reg[3] = 1;
}

// Allocate a free register. Return the number of the register.
// Die if no available registers.
static int alloc_register(void)
{
    for (int i = 0; i < 4; i++)
    {
        if (free_reg[i])
        {
            free_reg[i] = 0;
            return i;
        }
    }
    fprintf(stderr, "Out of registers!\n");
    exit(1);
}

// Return a register to the list of available registers.
// Check to see if it's not already there.
static void free_register(int reg)
{
    if (free_reg[reg] != 0)
    {
        fprintf(stderr, "Error trying to free register %d\n", reg);
        exit(1);
    }
    free_reg[reg] = 1;
}

// Print out the assembly preamble
void cg_preamble() {
    freeall_registers();
    fputs(
        "\t.text\n"
        ".LC0:\n"
        "\t.string\t\"%d\\n\"\n"
        "printint:\n"
        "\tpushq\t%rbp\n"
        "\tmovq\t%rsp, %rbp\n"
        "\tsubq\t$16, %rsp\n"
        "\tmovl\t%edi, -4(%rbp)\n"
        "\tmovl\t-4(%rbp), %eax\n"
        "\tmovl\t%eax, %esi\n"
        "\tleaq	.LC0(%rip), %rdi\n"
        "\tmovl	$0, %eax\n"
        "\tcall	printf@PLT\n"
        "\tnop\n"
        "\tleave\n"
        "\tret\n"
        "\n"
        "\t.globl\tmain\n"
        "\t.type\tmain, @function\n"
        "main:\n" "\tpushq\t%rbp\n" "\tmovq	%rsp, %rbp\n", Outfile
    );
}

// Print out the assembly postamble
void cg_postamble()
{
    fputs("\tmovl	$0, %eax\n" "\tpopq	%rbp\n" "\tret\n", Outfile);
}

// Load an integer literal value into a register.
// Return the number of the register
int cg_load(int value)
{
    // Get a new register
    int r = alloc_register();

    // Print out the code to initialize it
    fprintf(Outfile, "\tmovq\t$%d, %s\n", value, reg_list[r]);
    return r;
}

// Add two registers together and return
// the number of the register with the result
int cg_add(int r1, int r2)
{
    fprintf(Outfile, "\taddq\t%s, %s\n", reg_list[r1], reg_list[r2]);
    free_register(r1);
    return r2;
}

// Subtract the second register from the first and
// return the number of the register with the result
int cg_sub(int r1, int r2)
{
    fprintf(Outfile, "\tsubq\t%s, %s\n", reg_list[r2], reg_list[r1]);
    free_register(r2);
    return r1;
}

// Multiply two registers together and return
// the number of the register with the result
int cg_mul(int r1, int r2)
{
    fprintf(Outfile, "\timulq\t%s, %s\n", reg_list[r1], reg_list[r2]);
    free_register(r1);
    return r2;
}

// Divide the first register by the second and
// return the number of the register with the result
int cg_div(int r1, int r2)
{
    fprintf(Outfile, "\tmovq\t%s,%%rax\n", reg_list[r1]);
    fprintf(Outfile, "\tcqo\n");
    fprintf(Outfile, "\tidivq\t%s\n", reg_list[r2]);
    fprintf(Outfile, "\tmovq\t%%rax,%s\n", reg_list[r1]);
    free_register(r2);
    return r1;
}

// Call printint() with the given register
void cg_print_int(int r)
{
    fprintf(Outfile, "\tmovq\t%s, %%rdi\n", reg_list[r]);
    fprintf(Outfile, "\tcall\tprintint\n");
    free_register(r);
}
