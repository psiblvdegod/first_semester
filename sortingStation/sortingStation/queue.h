#pragma once
#include "stack.h"

typedef struct Queue Queue;

void enqueue(Queue * queue, char value, int * errorCode);

char dequeue(Queue* queue);

Queue* createQueue();

int queueSize(Queue * queue);

bool isEmptyQueue(Queue * queue);
