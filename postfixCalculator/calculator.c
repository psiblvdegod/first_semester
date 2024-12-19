#include "calculator.h"

bool inputValidation(const char *postfixNotation) {
    const char *validSymbols = "0123456789-+*/() ";
    for (int i = 0; postfixNotation[i] != '\0'; ++i) {
        bool validStatus = false;
        for (int j = 0; validSymbols[j] != '\0'; ++j) {
            if (postfixNotation[i] == validSymbols[j]) {
                validStatus = true;
                break;
            }
        }
        if (!validStatus) {
            return false;
        }
    }
    return true;
}

int calculator(const char *postfixNotation, bool *errorCode) {
    if (!inputValidation(postfixNotation)) {
        *errorCode = true;
        return -1;
    }
    Stack *stack = createStack(errorCode);
    if (*errorCode) {
        return -1;
    }
    for (int i = 0; postfixNotation[i] != '\0'; ++i) {
        char token = postfixNotation[i];
        if ('0' <= token && token <= '9') {
            push(stack, token - 48, errorCode);
            continue;
        }
        int operand1 = 0, operand2 = 0;
        if (token != ' ') {
            operand2 = pop(stack, errorCode);
            operand1 = pop(stack, errorCode);
        }
        if (token == '+') {
            push(stack, operand1 + operand2, errorCode);
        }
        if (token == '-') {
            push(stack, operand1 - operand2, errorCode);
        }
        if (token == '*') {
            push(stack, operand1 * operand2, errorCode);
        }
        if (token == '/') {
            push(stack, operand1 / operand2, errorCode);
        }
        if (*errorCode) {
            return -1;
        }
    }
    const int result = pop(stack, errorCode);
    deleteStack(&stack, errorCode);
    return result;
}
