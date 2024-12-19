#include "stack.h"

typedef struct StackElement {
    char value;
    struct StackElement * previous;
} StackElement;

struct Stack {
    StackElement * head;
};

Stack * createStack() {
    return (Stack *) calloc(1, sizeof(Stack));
}

void push(Stack * stack, char pushValue, bool * errorCode) {
    StackElement * element = malloc(sizeof(StackElement));
    if (element == NULL) {
        *errorCode = 1;
        return;
    }
    element->value = pushValue;
    element->previous = stack->head;
    stack->head = element;
}

char pop(Stack * stack) {
    char value = stack->head->value;
    StackElement * temp = stack->head;
    stack->head = stack->head->previous;
    free(temp);
    return value;
}

bool isEmptyStack(Stack * stack) {
    return stack->head == NULL;
}
