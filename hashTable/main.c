#include "errorCode.h"
#include "tests.h"

int main(void) {
    int errorCode = hashTableTests();
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    return hashTableFileTest();
}