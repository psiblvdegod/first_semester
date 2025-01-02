#include "errorCode.h"
#include "queue.h"
#include <stdlib.h>

typedef struct QueueElement {
    QueueValue value;
    struct QueueElement *previous;
} QueueElement;

struct Queue {
    QueueElement *front;
    QueueElement *back;
};

Queue *createQueue(int *errorCode) {
    Queue *queue = (Queue*)calloc(1, sizeof(struct Queue));
    if (queue == nullptr) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return nullptr;
    }
    return queue;
}

void enqueue(Queue *queue, QueueValue value, int *errorCode) {
    if (queue == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    QueueElement* newElement = (QueueElement*)calloc(1, sizeof(QueueElement));
    if (newElement == nullptr) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return;
    }
    newElement->value = value;
    if (queue->front == nullptr) {
        queue->front = newElement;
    }
    else {
        queue->back->previous = newElement;
    }
    queue->back = newElement;
}

QueueValue dequeue(Queue *queue, int *errorCode) {
    if (isEmptyQueue(queue, errorCode)) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return nullptr;
    }
    QueueValue value = queue->front->value;
    if (queue->front == queue->back) {
        free(queue->front);
        queue->front = nullptr;
        queue->back = nullptr;
    }
    else {
        QueueElement *temp = queue->front;
        queue->front = queue->front->previous;
        free(temp);
    }
    return value;
}

bool isEmptyQueue(Queue *queue, int *errorCode) {
    if (queue == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return true;
    }
    return queue->front == nullptr;
}

void releaseQueue(Queue *queue, int *errorCode) {
    while (!isEmptyQueue(queue, errorCode)) {
        dequeue(queue, errorCode);
    }
}

void deleteQueue(Queue **queue, int *errorCode) {
    if (queue == nullptr || *queue == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    releaseQueue(*queue, errorCode);
    free(*queue);
    *queue = nullptr;
}