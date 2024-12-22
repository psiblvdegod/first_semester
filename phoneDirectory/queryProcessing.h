#include "phoneDirectory.h"
#include <stdbool.h>

// if errorCode != 0 prints type of error happened.
// returns true if program can not continue working,
// else returns false.
bool reportError(int errorCode);

// processes user query.
// returns false if program should stop working,
// else returns true.
bool queryProcessing(Directory directory, const char *filePath, int *errorCode);