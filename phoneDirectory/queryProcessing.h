#include "phoneDirectory.h"
#include <stdbool.h>

// processes user query.
// returns false if program should stop working,
// else returns true.
bool queryProcessing(Directory directory, const char *filePath, int *errorCode);