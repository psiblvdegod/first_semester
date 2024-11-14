#include "stack.h"
#include <stdlib.h>

typedef struct StackElement {
    Node * node;
    struct StackElement * previous;
} StackElement ;

typedef struct Stack {
    StackElement * head;
} Stack;

Stack * createStack(bool * errorCode) {
    Stack * stack = calloc(1, sizeof(Stack));
    if (stack == NULL) {
        *errorCode = true;
    }
    return stack;
}

void push(Stack * stack, Node * node, bool * errorCode) {
    StackElement * newElement = calloc(1, sizeof(StackElement));
    if (newElement == NULL) {
        *errorCode = true;
        return;
    }
    newElement->node = node;
    newElement->previous = stack->head;
    stack->head = newElement;
}

Node * getHead(Stack * stack, bool * errorCode) {
    if (stack == NULL || stack->head == NULL) {
        *errorCode = true;
        return NULL;
    }
    return stack->head->node;
}

void pop(Stack * stack, bool * errorCode) {
    if (stack == NULL) {
        *errorCode = true;
        return;
    }
    StackElement * temp = stack->head;
    stack->head = stack->head->previous;
    free(temp);
}