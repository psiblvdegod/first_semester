#include "stack.h"
#include <stdlib.h>
#include "errorCode.h"

typedef struct StackElement {
    StackValue value;
    struct StackElement *previous;
} StackElement;

struct Stack {
    StackElement *head;
};

Stack *createStack(int *errorCode) {
    Stack *stack = calloc(1, sizeof(struct Stack));
    if (stack == nullptr) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
    }
    return stack;
}

void push(Stack *stack, StackValue value, int *errorCode) {
    if (value == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    if (stack == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    StackElement *newElement = calloc(1, sizeof(StackElement));
    if (newElement == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return;
    }
    newElement->value = value;
    newElement->previous = stack->head;
    stack->head = newElement;
}

StackValue pop(Stack *stack, int *errorCode) {
    if (stack == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return nullptr;
    }
    if (stack->head == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return nullptr;
    }
    StackValue value = stack->head->value;
    StackElement *temp = stack->head;
    stack->head = stack->head->previous;
    free(temp);
    return value;
}

bool isEmptyStack(Stack *stack, int *errorCode) {
    if (stack == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return true;
    }
    return stack->head == NULL;
}

void deleteStack(Stack **stack, int *errorCode) {
    if (stack == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    if ((*stack) == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    while (!isEmptyStack(*stack, errorCode)) {
        pop(*stack, errorCode);
    }
    free(*stack);
    *stack = nullptr;
}