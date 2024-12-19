#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct Stack Stack;

void push(Stack * stack, int value, int * errorCode);

int pop(Stack * stack);

Stack* createStack();
