#pragma once
#include "graph.h"

typedef int QueueValue;

typedef struct Queue* Queue;

void enqueue(Queue queue, QueueValue value);

QueueValue dequeue(Queue queue);
