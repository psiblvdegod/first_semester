#pragma once
#include <stdbool.h>
#include "tree.h"

typedef struct Stack Stack;

Stack * createStack(bool * errorCode);

void push(Stack * stack, Node * value, bool * errorCode);

Node * getHead(Stack * stack, bool * errorCode);

void pop(Stack * stack, bool * errorCode);