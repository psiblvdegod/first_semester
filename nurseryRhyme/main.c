#include "tests.h"
#include "errorCode.h"

int main(void) {
    int errorCode = NO_ERRORS;
    listTests(&errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    safePlaceTest(&errorCode);
    return errorCode;
}