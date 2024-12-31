#include "errorCode.h"
#include "tests.h"

int main(void) {
    int errorCode = graphTests();
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    return buildGraphTests("../text.txt");
}