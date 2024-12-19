#include "tests.h"

bool stackTest() {
    Stack * stack = createStack();
    if (stack == NULL) {
        return false;
    }
    bool errorCode = false;
    push(stack, '1', &errorCode);
    bool isEmptyTest = !isEmptyStack(stack);
    return pop(stack) == '1' && isEmptyTest && !errorCode;
}

bool parenthesesBalanceTest() {
    bool errorCode = false;
    bool test1 = parenthesesBalance("s(s[s[s]s(s)s(s)s{s}s]s)s{s}s", &errorCode);
    bool test2 = parenthesesBalance("s(s[s)s]s", &errorCode);
    bool test3 = parenthesesBalance("", &errorCode);
    return test1 && !test2 && test3 && !errorCode;
}