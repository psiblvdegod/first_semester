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
    Stack *stack = calloc(1, sizeof(Stack));
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

bool isEmpty(Stack *stack) {
    return stack == NULL || stack->head == NULL;
}

Value pop(Stack *stack, bool *errorCode) {
    if (isEmpty(stack)) {
        *errorCode = true;
        return 0;
    }
    Value value = stack->head->value;
    StackElement *temp = stack->head;
    stack->head = stack->head->previous;
    free(temp);
    return value;
}

void deleteStack(Stack **stack, bool *errorCode) {
    if (stack == NULL || *stack == NULL) {
        return;
    }
    while (!isEmpty(*stack)) {
        pop(*stack, errorCode);
    }
    free(*stack);
}