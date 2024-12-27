#pragma once
#include "tree.h"

// reads 16 symbols from standard input stream,
// converts it to signed int or reports an error.
int scanNumber(int *errorCode);

// processes user query
void queryProcessing(Node **root, int userQuery, int *errorCode);