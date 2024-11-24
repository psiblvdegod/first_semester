#include "commonestElement.h"
#include <stdlib.h>

int findCommonestElement(const int array[], const int arraySize, bool *errorCode) {
    if (array == NULL || arraySize < 0) {
        *errorCode = true;
        return 0;
    }
    int minElement = array[0], maxElement = array[0];
    for (int i = 1; i < arraySize; ++i) {
        minElement = array[i] < minElement ? array[i] : minElement;
        maxElement = array[i] > maxElement ? array[i] : maxElement;
    }
    const int elementsRange = maxElement - minElement + 1;
    int *elementCounter = calloc(elementsRange, sizeof(int));
    if (elementCounter == NULL) {
        *errorCode = true;
        return 0;
    }
    for (int j = 0; j < arraySize; ++j) {
        ++elementCounter[array[j] - minElement];
    }
    int result = 0, maxAmount = 0;
    for (int k = 0; k < elementsRange; ++k) {
        if (maxAmount < elementCounter[k]) {
            result = k + minElement;
            maxAmount = elementCounter[k];
        }
    }
    free(elementCounter);
    return result;
}