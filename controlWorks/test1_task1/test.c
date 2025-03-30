#include "test.h"
#include "queue.h"
#include "maxDigitSum.h"

#define NO_ERRORS 0
#define MEMORY_ALLOCATION_ERROR 44
#define INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION 1

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

void ordinaryMaxSumTest(int *errorCode) {
    const int array[5] = {10 , 20, 11, 2, 1001};
    const int arraySize = sizeof(array) / sizeof(int);
    Queue *queue = findNumbersWithMaxDigitSum(array, arraySize, errorCode);
    for (int i = 1; !isEmptyQueue(queue, errorCode); ++i) {
        if (array[i] != dequeue(queue, errorCode)) {
            if (*errorCode == NO_ERRORS) {
                *errorCode = -1;
            }
            break;
        }
    }
    deleteQueue(&queue, errorCode);
}

void unordinaryMaxSumTest(int *errorCode) {
    const int array[] = {12, 13, 14, 5, 23, 41, 14, 50, 500, 6};
    const int arraySize = sizeof(array) / sizeof(int);
    Queue *queue = findNumbersWithMaxDigitSum(array, arraySize, errorCode);
    const bool test = dequeue(queue, errorCode) == 6;
    deleteQueue(&queue, errorCode);
    if (*errorCode == 0 && !test) {
        *errorCode = -1;
    }
}