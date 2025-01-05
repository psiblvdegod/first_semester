#pragma once

#include <stdbool.h>

typedef struct Node* StackValue;

typedef struct Stack Stack;

// creates empty stack
Stack *createStack(int *errorCode);

// puts value to stack.
void push(Stack *stack, StackValue value, int *errorCode);

// deletes element from top of stack and returns it.
StackValue pop(Stack *stack, int *errorCode);

// if stack is empty returns true
// else returns false
bool isEmptyStack(Stack *stack, int *errorCode);

// frees allocated memory turns pointer NULL
void deleteStack(Stack **stack, int *errorCode);