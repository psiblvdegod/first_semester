#pragma once
#include "tree.h"
#include <stdbool.h>

typedef struct StackElement *Stack;

typedef Node *StackElementValue;

// adds element to stack
void push(Stack *stack, Node *value, int *errorCode);

// gets node from the top of the stack
Node *getHead(Stack stack, int *errorCode);

// deletes element from the top of the stack
void pop(Stack *stack, int *errorCode);

// frees allocated memory turns pointer NULL
void deleteStack(Stack *stack, int *errorCode);