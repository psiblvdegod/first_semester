#include "parenthesesBalance.h"

bool parenthesesBalance(const char *string, bool *errorCode) {
    if (string == NULL) {
        *errorCode = true;
        return true;
    }
    Stack stack = NULL;
    for (int i = 0; string[i] != '\0'; ++i) {
        if (string[i] == '(' || string[i] == '{' || string[i] == '[') {
            push(&stack, string[i], errorCode);
            if (*errorCode) {
                return false;
            }
        }
        if (string[i] == ')' || string[i] == '}' || string[i] == ']') {
            Value parenthesis = pop(&stack, errorCode);
            if (*errorCode) {
                return false;
            }
            if (parenthesis == '(' && string[i] != ')') {
                return false;
            }
            if (parenthesis == '{' && string[i] != '}') {
                return false;
            }
            if (parenthesis == '[' && string[i] != ']') {
                return false;
            }
        }
    }
    return true;
}
