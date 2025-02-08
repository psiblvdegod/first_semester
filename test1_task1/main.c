#include "test.h"

#define NO_ERRORS 0
#define MEMORY_ALLOCATION_ERROR 44
#define INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION 1

int main(void) {
    int errorCode = NO_ERRORS;
    queueTest(&errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    ordinaryMaxSumTest(&errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    unordinaryMaxSumTest(&errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
}
