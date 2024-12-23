#include "test.h"
#include "queue.h"
#include "commentsScan.h"

void queueTest(int *errorCode) {
    Queue *queue = createQueue(errorCode);
    if (*errorCode != 0) {
        return;
    }
    enqueue(queue, '1', errorCode);
    enqueue(queue, '2', errorCode);
    enqueue(queue, '3', errorCode);
    const bool test1 = dequeue(queue, errorCode) == '1';
    const bool test2 = dequeue(queue, errorCode) == '2';
    const bool test3 = dequeue(queue, errorCode) == '3';
    const bool test = test1 && test2 && test3;
    if (*errorCode == 0 && !test) {
        *errorCode = -1;
    }

}

void commentsScanTest(int *errorCode) {
    const char *string = ";s1\n;s3";
    Queue *queue = scanCommentsFromFile("../text.txt", errorCode);
    for (int i = 0; !isEmptyQueue(queue); ++i) {
        if (string[i] != dequeue(queue, errorCode)) {
            if (*errorCode == 0) {
                *errorCode = -1;
            }
            return;
        }
    }
}