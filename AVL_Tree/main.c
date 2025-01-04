#include "tests.h"
#include "errorCode.h"

int main(void) {
    int errorCode = invariantTest("../test.txt");
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    errorCode = AVLTreeTest();
    return errorCode;
}