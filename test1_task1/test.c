#include "test.h"
#include "queue.h"
#include "maxDigitSum.h"

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
    deleteQueue(&queue, errorCode);
    const bool test = test1 && test2 && test3;
    if (*errorCode == 0 && !test) {
        *errorCode = -1;
    }
}

void maxDigitSumTest(int *errorCode) {
    const int array[5] = {10 , 20, 11, 2, 1001};
    const int arraySize = sizeof(array) / sizeof(int);
    Queue *queue = findNumbersWithMaxDigitSum(array, arraySize, errorCode);
    int a = 0;
}