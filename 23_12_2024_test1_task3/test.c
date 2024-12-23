#include "test.h"
#include "queue.h"

int queueTest() {
    int errorCode = 0;
    Queue *queue = createQueue(&errorCode);
    if (errorCode) {
        return errorCode;
    }
    enqueue(queue, '1', &errorCode);
    enqueue(queue, '2', &errorCode);
    enqueue(queue, '3', &errorCode);
    const bool test1 = dequeue(queue, &errorCode) == '1';
    const bool test2 = dequeue(queue, &errorCode) == '2';
    const bool test3 = dequeue(queue, &errorCode) == '3';
    const bool test = test1 && test2 && test3;
    if (errorCode == 0 && !test) {
        return -1;
    }
    return errorCode;
}

int