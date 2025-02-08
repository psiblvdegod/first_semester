#include "stack.h"

typedef struct StackElement {
    Value value;
    struct StackElement *previous;
} StackElement;

void push(Stack *stack, Value value, bool *errorCode) {
    StackElement *newElement = calloc(1, sizeof(StackElement));
    if (newElement == NULL) {
        *errorCode = true;
        return;
    }
    newElement->value = value;
    newElement->previous = *stack;
    *stack = newElement;
}

Value pop(Stack *stack, bool *errorCode) {
    if (isEmptyStack(stack)) {
        *errorCode = true;
        return '1';
    }
    Value value = (*stack)->value;
    StackElement *temp = *stack;
    *stack = (*stack)->previous;
    free(temp);
    return value;
}

bool isEmptyStack(Stack *stack) {
    return stack == NULL || *stack == NULL;
}
