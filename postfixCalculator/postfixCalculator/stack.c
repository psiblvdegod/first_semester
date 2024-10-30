#include "stack.h"

typedef struct StackElement {
    int value;
    struct StackElement * previous;
} StackElement;

struct Stack {
    StackElement * head;
};

Stack * createStack() {
    return (Stack *) calloc(1, sizeof(Stack));
}

void push(Stack * stack, int pushValue, int * errorCode) {
    StackElement * element = malloc(sizeof(StackElement));
    if (element == NULL) {
        *errorCode = 1;
        return;
    }
    element->value = pushValue;
    element->previous = stack->head;
    stack->head = element;
}

int pop(Stack * stack) {
    int value = stack->head->value;
    StackElement * temp = stack->head;
    stack->head = stack->head->previous;
    free(temp);
    return value;
}
