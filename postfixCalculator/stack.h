#pragma once
#include <stdbool.h>

typedef int Value;

typedef struct Stack Stack;

// creates stack,
// report an error if memory allocation is failed.
Stack *createStack(bool *errorCode);

// puts value on the top of the stack.
// report an error if memory allocation is failed.
void push(Stack *stack, Value value, bool *errorCode);

// deletes element from the top of the stack and returns it.
// reports an error if stack is empty.
Value pop(Stack *stack, bool *errorCode);

// deletes stack.
void deleteStack(Stack **stack, bool *errorCode);