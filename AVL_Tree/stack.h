#pragma once

#include <stdbool.h>

typedef struct Node* StackValue;

typedef struct Stack Stack;

Stack *createStack(int *errorCode);

// puts value to stack.
// reports an error if memory allocation is failed.
void push(Stack *stack, StackValue value, int *errorCode);

// deletes element from top of stack and returns it.
// report an error if stack is empty.
StackValue pop(Stack *stack, int *errorCode);

// returns true if stack == NULL or stack is empty.
bool isEmptyStack(Stack *stack, int *errorCode);

void deleteStack(Stack **stack, int *errorCode);