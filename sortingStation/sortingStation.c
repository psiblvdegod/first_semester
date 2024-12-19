#include "sortingStation.h"

void convertInfixToPostfix(const char *input, Stack *stack, Queue *queue, bool *errorCode) {
    for (int i = 0; input[i] != '\0'; ++i) {
        const char token = input[i];
        if (('0' <= token) && (token <='9')) {
            enqueue(queue, token, errorCode);
        }
        if (token == '*' || token == '/' || token == '+' || token == '-') {
            while (!isEmptyStack(stack)) {
                const char stackToken = pop(stack, errorCode);
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
                char stackToken = pop(stack, errorCode);
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
        enqueue(queue, pop(stack, errorCode), errorCode);
    }
}
