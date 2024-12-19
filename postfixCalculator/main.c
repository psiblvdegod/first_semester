#include "stack.h"
#include "tests.h"
#include "calculator.h"

int main(void) {
    if (!stackTest() || !calculatorTest()) {
        printf("Error. Tests failed.\n");
        return -1;
    }
    Stack * stack = createStack();
    if (stack == NULL) {
        printf("Memory allocation error.\n");
        return -1;
    }
    int errorCode = 0;
    char * postfixNotation = "1 2 + 3 4 * -";
    if (!inputValidation(postfixNotation)) {
        printf("Error. Invalid value.\n");
        return -1;
    }
    calculator(stack, postfixNotation, &errorCode);
    if (errorCode) {
        printf("Error.\n");
        return -1;
    }
    printf("result: %d", pop(stack));
}
