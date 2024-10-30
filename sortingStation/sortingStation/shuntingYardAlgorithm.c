#include "stack.h"
#include "queue.h"

bool inputValidation(char * string) {
    char * validCharacters = "0123456789()+-*/ ";
    int parenthesesBalance = 0;
    for (int k = 0; string[k] != '\0'; ++k) {
        bool validStatus = false;
        for (int i = 0; i < 17; ++i) {
            if (string[k] == validCharacters[i]) {
                validStatus = true;
            }
            if (string[k] == '(') {
                ++parenthesesBalance;
            }
            if (string[k] == ')') {
                --parenthesesBalance;
                if (parenthesesBalance < 0) {
                    return false;
                }
            }
        }
        if (!validStatus) {
            return false;
        }
    }
    return (!parenthesesBalance);
}

void shuntingYardAlgorithm(char * inputStream, Stack * stack, Queue * queue, int * errorCode) {
    for (int i = 0; inputStream[i] != '\0'; ++i) {
        char token = inputStream[i];
        if (('0' <= token) && (token <='9')) {
            enqueue(queue, token, errorCode);
        }
        if (token == '*' || token == '/' || token == '+' || token == '-') {
            while (!isEmptyStack(stack)) {
                char stackToken = pop(stack);
                if (stackToken == '(' || stackToken == ')') {
                    push(stack, stackToken, errorCode);
                    break;
                }
                if (token == '+' || token == '-' || ((token == '*' || token == '/') && (stackToken == '*' || stackToken == '/'))) {
                    enqueue(queue, ' ', errorCode);
                    enqueue(queue, stackToken, errorCode);
                    
                }
                else {
                    push(stack, stackToken, errorCode);
                    break;
                }
            }
            enqueue(queue, ' ', errorCode);
            push(stack, token, errorCode);
        }
        if (token == '(') {
            push(stack, token, errorCode);
        }
        if (token == ')') {
            while (!isEmptyStack(stack)) {
                char stackToken = pop(stack);
                if (stackToken == '(') {
                    break;
                }
                enqueue(queue, ' ', errorCode);
                enqueue(queue, stackToken, errorCode);
            }
        }
    }
    while (!isEmptyStack(stack)) {
        enqueue(queue, ' ', errorCode);
        enqueue(queue, pop(stack), errorCode);
    }
}
