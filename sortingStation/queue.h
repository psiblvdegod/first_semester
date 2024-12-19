#pragma once
#include "stack.h"

typedef struct Queue Queue;

Queue *createQueue(bool *errorCode);

void enqueue(Queue *queue, Value value, bool *errorCode);

Value dequeue(Queue *queue, bool *errorCode);

bool isEmptyQueue(Queue *queue);
