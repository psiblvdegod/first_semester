#pragma once
#include <stdbool.h>

typedef struct Queue Queue;

typedef int Value;

// creates empty queue
Queue *createQueue(int *errorCode);

// adds elements to queue
void enqueue(Queue *queue, Value value, int *errorCode);

// deletes earliest added element and returns it's value
Value dequeue(Queue *queue, int *errorCode);

// if queue is empty returns true,
// else returns false.
bool isEmptyQueue(Queue *queue, int *errorCode);

// frees allocated memory and turns pointer NULL
void deleteQueue(Queue **queue, int *errorCode);

// deletes all elements from queue
void releaseQueue(Queue *queue, int *errorCode);