#pragma once
#include "graph.h"
#include <stdbool.h>

typedef struct Vertex* QueueValue;

typedef struct Queue* Queue;

Queue createQueue();

// adds element to queue.
void enqueue(Queue queue, QueueValue value);

// delete element from queue and returns it.
QueueValue dequeue(Queue queue);

bool isQueueEmpty(Queue queue);