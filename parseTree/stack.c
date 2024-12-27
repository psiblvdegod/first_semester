#include "stack.h"
#include "errorCode.h"
#include <stdlib.h>

typedef struct StackElement {
    StackElementValue value;
    struct StackElement *previous;
} StackElement;

void push(Stack *stack, StackElementValue value, int *errorCode) {
    if (stack == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    StackElement *newElement = calloc(1, sizeof(StackElement));
    if (newElement == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return;
    }
    newElement->value = value;
    newElement->previous = *stack;
    *stack = newElement;
}

Node *getHead(Stack stack, int *errorCode) {
    if (stack == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return NULL;
    }
    return stack->value;
}

void pop(Stack *stack, int *errorCode) {
    if (stack == NULL || *stack == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    StackElement *temp = *stack;
    *stack = (*stack)->previous;
    free(temp);
}

void deleteStack(Stack *stack, int *errorCode) {
    if (stack == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    while (*stack != NULL) {
        pop(stack, errorCode);
    }
}