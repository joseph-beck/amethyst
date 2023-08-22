#pragma once

#define extern_
#include "data.h"
#undef extern_

#include <stdio.h>
#include <errno.h>

#include "expr.h"
#include "tokens.h"
#include "interp.h"
#include "tree.h"
#include "scan.h"
#include "cg.h"
#include "gen.h"