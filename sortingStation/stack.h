#pragma once
#include <stdbool.h>

typedef char Value;

typedef struct Stack Stack;

Stack *createStack(bool *errorCode);

// puts value to stack.
// reports an error if memory allocation is failed.
void push(Stack *stack, Value value, bool *errorCode);

// deletes element from top of stack and returns it.
// report an error if stack is empty.
Value pop(Stack *stack, bool *errorCode);

// returns true if stack == NULL or stack is empty.
bool isEmptyStack(Stack *stack);