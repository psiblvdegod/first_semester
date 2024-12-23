#include "queue.h"
#include <stdlib.h>

#define MEMORY_ALLOCATION_ERROR 44
#define INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION 1

typedef struct QueueElement {
    Value value;
    struct QueueElement *previous;
} QueueElement;

struct Queue {
    QueueElement *front;
    QueueElement *back;
};

Queue *createQueue(int *errorCode) {
    Queue *queue = (Queue*)calloc(1, sizeof(struct Queue));
    if (queue == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }
    return queue;
}

void enqueue(Queue *queue, Value value, int *errorCode) {
    if (queue == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    QueueElement* newElement = (QueueElement*)calloc(1, sizeof(QueueElement));
    if (newElement == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        free(newElement);
        return;
    }
    newElement->value = value;
    if (queue->front == NULL) {
        queue->front = newElement;
    }
    else {
        queue->back->previous = newElement;
    }
    queue->back = newElement;
}

Value dequeue(Queue *queue, int *errorCode) {
    if (isEmptyQueue(queue, errorCode)) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return -1;
    }
    Value value = queue->front->value;
    if (queue->front == queue->back) {
        free(queue->front);
        queue->front = NULL;
        queue->back = NULL;
    }
    else {
        QueueElement *temp = queue->front;
        queue->front = queue->front->previous;
        free(temp);
    }
    return value;
}

bool isEmptyQueue(Queue *queue, int *errorCode) {
    if (queue == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return true;
    }
    return queue->front == NULL;
}

void releaseQueue(Queue *queue, int *errorCode) {
    while (!isEmptyQueue(queue, errorCode)) {
        dequeue(queue, errorCode);
    }
}

void deleteQueue(Queue **queue, int *errorCode) {
    if (queue == NULL || *queue == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    releaseQueue(*queue, errorCode);
    free(*queue);
    *queue = NULL;
}