#include "phoneDirectory.h"
#include <stdbool.h>

// if errorCode != 0 prints type of error happened.
// returns false if program can not continue working,
// else return true.
bool errorMessage(int errorCode);

bool queryProcessing(Directory directory, const char *filePath, int *errorCode);