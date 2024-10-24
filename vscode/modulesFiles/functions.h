#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

typedef struct Stack Stack;
Stack* createStack();
void push(Stack * stack, int value, int * errorCode);
int pop(Stack * stack);
int commonestElement(Stack * stack, int arraySize, int *errorCode);
bool commonestElementTest();