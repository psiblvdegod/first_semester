#pragma once
#include "graph.h"
#include <stdbool.h>

typedef struct Vertex* QueueValue;

typedef struct Queue* Queue;

Queue createQueue();

void enqueue(Queue queue, QueueValue value);

QueueValue dequeue(Queue queue);

bool isQueueEmpty(Queue queue);