#include "stack.h"
#include <stdlib.h>

typedef struct StackElement {
    Value value;
    struct StackElement *previous;
} StackElement;

struct Stack {
    StackElement *head;
};

Stack *createStack(bool *errorCode) {
    Stack *stack = calloc(1, sizeof(struct Stack));
    if (stack == NULL) {
        *errorCode = true;
    }
    return stack;
}

void push(Stack *stack, Value value, bool *errorCode) {
    StackElement *newElement = calloc(1, sizeof(StackElement));
    if (newElement == NULL) {
        *errorCode = true;
        return;
    }
    newElement->value = value;
    newElement->previous = stack->head;
    stack->head = newElement;
}

Value pop(Stack *stack, bool *errorCode) {
    if (isEmptyStack(stack)) {
        *errorCode = true;
        return '1';
    }
    Value value = stack->head->value;
    StackElement *temp = stack->head;
    stack->head = stack->head->previous;
    free(temp);
    return value;
}

bool isEmptyStack(Stack *stack) {
    return stack == NULL || stack->head == NULL;
}