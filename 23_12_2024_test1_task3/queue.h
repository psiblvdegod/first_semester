#include <stdbool.h>
#pragma once

typedef struct Queue Queue;

typedef char Value;

Queue *createQueue(int *errorCode);

void enqueue(Queue *queue, Value value, int *errorCode);

Value dequeue(Queue *queue, int *errorCode);

bool isEmptyQueue(Queue *queue);