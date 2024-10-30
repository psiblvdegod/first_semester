#include "tests.h"

bool stackTest() {
    Stack * testStack = createStack();
    if (testStack == NULL) {
        return false;
    }
    int errorCode = 0;
    push(testStack, 200, &errorCode);
    return pop(testStack) == 200 && !errorCode;
}

bool calculatorTest() {
    Stack * testStack = createStack();
    if (testStack == NULL) {
        return false;
    }
    int errorCode = 0;
    calculator(testStack, "1 2 3 - + 7 *", &errorCode);
    return !pop(testStack);
}
