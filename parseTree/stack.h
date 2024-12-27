#pragma once
#include <stdbool.h>
#include "tree.h"

typedef struct StackElement *Stack;

typedef Node *StackElementValue;

void push(Stack *stack, Node *value, int *errorCode);

Node *getHead(Stack stack, int *errorCode);

void pop(Stack *stack, int *errorCode);

void deleteStack(Stack *stack, int *errorCode);