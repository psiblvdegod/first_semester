#include "tests.h"
#include "errorCode.h"

int main(void) {
   int errorCode = NO_ERRORS;
    stackTests(&errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    treeTests(&errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    parseTreeTests(&errorCode);
    return errorCode;
}
