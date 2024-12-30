#pragma once
#include <stdbool.h>
#include "list.h"

// process user query.
// returns false if program should stop working,
// else returns true.
bool queryProcessing(List *list, int *errorCode);