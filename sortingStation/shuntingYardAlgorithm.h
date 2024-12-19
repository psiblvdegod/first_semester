#pragma once 
#include "stack.h"
#include "queue.h"

void shuntingYardAlgorithm(char *inputStream, Stack *stack, Queue *queue, int * errorCode);

bool inputValidation(char *string);
