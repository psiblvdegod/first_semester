#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct Stack Stack;

void push(Stack * stack, char value, bool * errorCode);

char pop(Stack * stack);

Stack* createStack();

bool isEmptyStack(Stack * stack);
