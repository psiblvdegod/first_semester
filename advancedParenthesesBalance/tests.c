#include "tests.h"

bool stackTest() {
    Stack stack = NULL;
    bool errorCode = false;
    push(&stack, '1', &errorCode);
    bool isEmptyTest = !isEmptyStack(&stack);
    return pop(&stack, &errorCode) == '1' && isEmptyTest && !errorCode;
}

bool parenthesesBalanceTest() {
    bool errorCode = false;
    bool test1 = parenthesesBalance("s(s[s[s]s(s)s(s)s{s}s]s)s{s}s", &errorCode);
    bool test2 = !parenthesesBalance("s(s[s)s]s", &errorCode);
    bool test3 = parenthesesBalance("", &errorCode);
    return test1 && test2 && test3 && !errorCode;
}