#pragma once
#include <stdlib.h>
#include <stdbool.h>

typedef struct Stack Stack;

void push(Stack * stack, char value, int * errorCode);

char pop(Stack * stack);

Stack* createStack();

bool isEmptyStack(Stack * stack);
