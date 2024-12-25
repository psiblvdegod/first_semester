#include "tests.h"
#include "errorCode.h"

int main(void) {
    int errorCode = NO_ERRORS;
    mergeTest(&errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    mergeSortTest(&errorCode);
    return errorCode;
}