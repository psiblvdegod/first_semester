#include "queue.h"

typedef struct QueueElement {
    char value;
    struct QueueElement* next;
} QueueElement;

struct Queue {
    QueueElement* front; 
    QueueElement* back;  
};

Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        return NULL;
    }
    queue->front = NULL;
    queue->back = NULL;
    return queue;
}

void enqueue(Queue* queue, char value, int * errorCode) {
    QueueElement* element = (QueueElement*)malloc(sizeof(QueueElement));
    if (element == NULL) {
        *errorCode = 1;
        return;
    }
    element->value = value;
    element->next = NULL;
    if (queue->front == NULL) {
        queue->front = element; 
        queue->back = element;
    }
    else {
        queue->back->next = element;
        queue->back = element;
    }
}

char dequeue(Queue* queue) {
    char value = queue->front->value;
    QueueElement* tmp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->back = NULL;
    }
    free(tmp);
    return value;
}

int queueSize(Queue * queue) {
    if (queue->front == NULL) {
        return 0;
    }
    QueueElement * fromFrontToBack = queue->front;
    int result = 1;
    while (fromFrontToBack != queue->back) {
        ++result;
        fromFrontToBack = fromFrontToBack->next;
    }
    return result;
}

bool isEmptyQueue(Queue *queue) {
    return (queue->front == NULL);
}
