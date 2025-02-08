#include "test.h"

#define INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION 1
#define MEMORY_ALLOCATION_ERROR 44
#define TESTS_FAILED_ERROR (-1)
#define NO_ERRORS 0

int main(void) {
    int errorCode = NO_ERRORS;
    listTests(&errorCode);
    if (errorCode != 0) {
        return errorCode;
    }
    copyListElements(&errorCode);
    return errorCode;
}