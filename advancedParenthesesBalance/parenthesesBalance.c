#include "parenthesesBalance.h"

bool parenthesesBalance(char * string, bool * errorCode) {
    Stack * mainStack = createStack();
    Stack * rightParenthesesStack = createStack();
    if (mainStack == NULL || rightParenthesesStack == NULL) {
        *errorCode = true;
        return false;
    }
    char * parentheses = "()[]{}";
    for (int i = 0; string[i] != '\0'; ++i) {
        for (int k = 0; parentheses[k] != '\0'; ++k) {
            if (string[i] == parentheses[k]) {
                push(mainStack, string[i], errorCode);
            }
        }
    }
    while (!isEmptyStack(mainStack)) {
        char right = '0';
        if (!isEmptyStack(rightParenthesesStack)) {
            right = pop(rightParenthesesStack);
        }
        else {
            right = pop(mainStack);
        }
        if (right == '(' || right == '{' || right == '[') {
            return false;
        }
        char left = '0';
        if (!isEmptyStack(mainStack)) {
            left = pop(mainStack);
        }
        else {
            return false;
        }
        if (left == ')' || left == ']' || left == '}') {
            push(rightParenthesesStack, right, errorCode);
            push(rightParenthesesStack, left, errorCode);
            continue;
        }
        switch (right) {
            case ')':
                if (left == '(') {
                    break;
                }
                if (left == '{' || left == '[') {
                    return false;
                }
            case ']':
                if (left == '[') {
                    break;
                }
                if (left == '{' || left == '(') {
                    return false;
                }
            case '}':
                if (left == '{') {
                    break;
                }
                if (left == '(' || left == '[') {
                    return false;
                }
        }
    }
    return true;
}
