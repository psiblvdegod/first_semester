#include "sorting.h"
#include <stdlib.h>

void swap(int *left, int *right) {
    if (*left == *right) {
        return;
    }
    *left = *left + *right;
    *right = *left - *right;
    *left = *left - *right;
}

void bubbleSort(int array[], const int arraySize) {
    while (true) {
        bool wasSwap = false;
        for (int i = 1; i < arraySize; ++i) {
            if (array[i] < array[i - 1]) {
                wasSwap = true;
                swap(&array[i], &array[i - 1]);
            }
        }
        if (!wasSwap) {
            return;
        }
    }
}

void countingSort(int array[], const int arraySize, bool * errorCode) {
    int maxElement = array[0], minElement = array[0];
    for (int m = 1; m < arraySize; ++m) {
        maxElement = array[m] > maxElement ? array[m] : maxElement;
        minElement = array[m] < minElement ? array[m] : minElement;
    }
    const int elementsRange = maxElement - minElement + 1;
    int *amountOfElements = calloc(elementsRange, sizeof(int));
    if (amountOfElements == NULL) {
        *errorCode = true;
        return;
    }
    for (int l = 0; l < arraySize; ++l) {
        ++amountOfElements[array[l] - minElement];
    }
    for (int j = 0, i = 0; j < elementsRange; ++j) {
        for (int k = 0; k < amountOfElements[j]; ++k, ++i) {
            array[i] = j + minElement;
        }
    }
    free(amountOfElements);
}