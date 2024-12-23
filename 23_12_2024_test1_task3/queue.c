#include "queue.h"
#include <stdlib.h>

typedef struct QueueElement {
    Value value;
    struct QueueElement* previous;
} QueueElement;

struct Queue {
    QueueElement *front;
    QueueElement *back;
};

Queue *createQueue(int *errorCode) {
    Queue *queue = (Queue*)calloc(1, sizeof(struct Queue));
    if (queue == NULL) {
        *errorCode = 1;
        free(queue);
        return NULL;
    }
    return queue;
}

void enqueue(Queue *queue, Value value, int *errorCode) {
    if (queue == NULL) {
        *errorCode = 1;
        return;
    }
    QueueElement* newElement = (QueueElement*)calloc(1, sizeof(QueueElement));
    if (newElement == NULL) {
        *errorCode = 1;
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
    if (isEmptyQueue(queue)) {
        *errorCode = 1;
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

bool isEmptyQueue(Queue *queue) {
    return (queue == NULL || queue->front == NULL);
}

void deleteQueue(Queue **queue, int *errorCode) {
    if (queue == NULL || *queue == NULL) {
        *errorCode = 1;
        return;
    }
    while ((*queue)->front != NULL) {
        dequeue(*queue, errorCode);
    }
    free(*queue);
    *queue = NULL;
}