#include "symbol.h"
#include "data.h"
#include "fatal.h"

static int globs = 0;

// Determine if the symbol s is in the global symbol table.
// Return its slot position or -1 if not found.
int find_glob(char* s)
{
    int i;

    for (i = 0; i < globs; i++)
    {
        if (*s == *Gsym[i].name && !strcmp(s, Gsym[i].name))
        {
            return (i);
        }
    }
    return (-1);
}

// Get the position of a new global symbol slot, or die
// if we've run out of positions.
static int new_glob()
{
    int p;

    if ((p = globs++) >= NSYMBOLS)
    {
        fatal("Too many global symbols");
    }
    
    return (p);
}

// Add a global symbol to the symbol table.
// Return the slot number in the symbol table
int add_glob(char* name)
{
    int y;

    // If this is already in the symbol table, return the existing slot
    if ((y = find_glob(name)) != -1)
    {
        return (y);
    }

    // Otherwise get a new slot, fill it in and
    // return the slot number
    y = new_glob();
    Gsym[y].name = strdup(name);
    return (y);
}
