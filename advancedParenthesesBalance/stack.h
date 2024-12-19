#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef char Value;

typedef struct StackElement *Stack;

// puts value to stack.
// reports an error if memory allocation is failed.
void push(Stack *stack, Value value, bool *errorCode);

// deletes element from top of stack and returns it.
// report an error if stack is empty.
Value pop(Stack *stack, bool *errorCode);

// returns true if stack == NULL or stack is empty.
bool isEmptyStack(Stack *stack);