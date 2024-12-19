#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef char Value;

typedef struct StackElement *Stack;

// puts value to stack.
void push(Stack *stack, Value value, bool *errorCode);

// deletes element from top of stack and returns it.
Value pop(Stack *stack, bool *errorCode);

// returns true if stack == NULL or stack is empty.
bool isEmptyStack(Stack *stack);