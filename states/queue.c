#include "queue.h"
#include <stdlib.h>

typedef struct QueueElement {
    QueueValue value;
    struct QueueElement *previous;
} QueueElement;

struct Queue {
    QueueElement *head;
    QueueElement *tail;
};

void enqueue(Queue queue, QueueValue value) {
    QueueElement *newElement = calloc(1, sizeof(QueueElement));
    if (newElement == NULL) {
        return;
    }
    newElement->value = value;
    if (queue->head == NULL) {
        queue->head = newElement;
    }
    else if (queue->tail != NULL) {
        queue->tail->previous = newElement;
    }
    queue->tail = newElement;
}

QueueValue dequeue(Queue queue) {
    if (queue == NULL || queue->head == NULL) {
        return -1;
    }
    QueueElement *temp = queue->head;
    QueueValue value = queue->head->value;
    if (queue->head == queue->tail) {
        queue->tail = NULL;
    }
    queue->head = queue->head->previous;
    free(temp);
    return value;
}