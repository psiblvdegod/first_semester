#include "maxDigitSum.h"

Queue *findNumbersWithMaxDigitSum(const int *array, const int arraySize, int *errorCode) {
    Queue *queue = createQueue(errorCode);
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
    }
    return queue;
}