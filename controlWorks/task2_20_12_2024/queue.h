#include <stdbool.h>
#pragma once

typedef struct Queue Queue;

typedef int Value;

Queue *createQueue(bool *errorCode);

void enqueue(Queue *queue, Value value, bool *errorCode);

Value dequeue(Queue *queue, bool *errorCode);

bool isEmptyQueue(Queue *queue);