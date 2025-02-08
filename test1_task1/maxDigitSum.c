#include "maxDigitSum.h"
#include <stdlib.h>

#define NO_ERRORS 0
#define MEMORY_ALLOCATION_ERROR 44
#define INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION 1

Queue *findNumbersWithMaxDigitSum(const int *array, const int arraySize, int *errorCode) {
    if (array == NULL || arraySize < 1) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return NULL;
    }
    Queue *queue = createQueue(errorCode);
    if (*errorCode != 0) {
        return NULL;
    }
    int maxSum = -1;
    for (int i = 0; i < arraySize; ++i) {
        int currentNumber = array[i];
        int currentDigitSum = 0;
        while (currentNumber != 0) {
            currentDigitSum += currentNumber % 10;
            currentNumber /= 10;
        }
        if (currentDigitSum == maxSum) {
            enqueue(queue, array[i], errorCode);
        }
        else if (currentDigitSum > maxSum) {
            maxSum = currentDigitSum;
            releaseQueue(queue, errorCode);
            enqueue(queue, array[i], errorCode);
        }
        if (*errorCode != 0) {
            return NULL;
        }
    }
    return queue;
}

