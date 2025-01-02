#include "tests.h"
#include "errorCode.h"

int main(void) {
    int errorCode = stackTests();
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    errorCode = treeTests();
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    errorCode = parseTests("../text.txt");
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    errorCode = queueTest();
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    errorCode = treeTraversalTest();
    return errorCode;
}