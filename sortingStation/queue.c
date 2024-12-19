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

Queue *createQueue(bool *errorCode) {
    Queue *queue = (Queue*)calloc(1, sizeof(struct Queue));
    if (queue == NULL) {
        *errorCode = true;
    }
    return queue;
}

void enqueue(Queue *queue, Value value, bool *errorCode) {
    QueueElement* newElement = (QueueElement*)calloc(1, sizeof(QueueElement));
    if (newElement == NULL) {
        *errorCode = true;
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

Value dequeue(Queue *queue, bool *errorCode) {
    if (isEmptyQueue(queue)) {
        *errorCode = true;
        return 0;
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
