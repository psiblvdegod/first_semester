#pragma once
#include <stdlib.h>
#include "stack.h"

// calculates an expression in postfix notation.
// reports an error if input is incorrect.
int calculator(const char *string, bool *errorCode);