#include "tests.h"
#include "errorCode.h"

int main(void) {
    int errorCode = NO_ERRORS;
    listTests(&errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    mergeTest(&errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    mergeSortTest(&errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    contactsSortingTest(&errorCode);
    return errorCode;
}