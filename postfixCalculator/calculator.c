#include "calculator.h"

bool inputValidation(char * postfixNotation) {
    char * validSymbols = "0123456789-+*/ ";
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


int calculator(Stack * stack, char * postfixNotation, int * errorCode) {
    for (int i = 0; postfixNotation[i] != '\0'; ++i) {
        char token = postfixNotation[i];
        if ('0' <= token && token <= '9') {
            push(stack, token - 48, errorCode); //char ASCII number '0' = 48, '1' = 49 ...
            continue;
        }
        int operand1 = 0, operand2 = 0;
        if (token != ' ') {
            operand2 = pop(stack);
            operand1 = pop(stack);
        }
        if (token == '+') {
            push(stack, operand1 + operand2, errorCode);
        }
        if (token == '-') {
            push(stack, operand1 - operand2, errorCode);
        }
        if (token == '*') {
            push(stack, operand1 * operand2 , errorCode);
        }
        if (token == '/') {
            push(stack, operand1 / operand2, errorCode);
        }
    }
}
