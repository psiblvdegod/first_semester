#include "tests.h"

bool stackTest() {
    bool errorCode = false;
    Stack *stack = createStack(&errorCode);
    if (errorCode) {
        return false;
    }
    push(stack, 1, &errorCode);
    const bool test = pop(stack, &errorCode) == 1;
    deleteStack(&stack, &errorCode);
    return test && !errorCode;
}

bool calculatorTest() {
    bool errorCode = false;
    const bool test1 = calculator("1 2 3 - + 7 *", &errorCode) == 0;
    const bool test2 = calculator("7 2 1 - *", &errorCode) == 7;
    const bool test3 = calculator("8 4 3 - / 7 -", &errorCode) == 1;
    return test1 && test2 && test3 && !errorCode;
}
