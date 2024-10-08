#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int commonestElement(int array[], int arraySize, int *errorCode) {
    if (arraySize < 0) {
        *errorCode = 1;
        return 0;
    }
    int minElement = 100000, maxElement = -100000;
    for (int i = 0; i < arraySize; ++i) {
        minElement = array[i] < minElement ? array[i] : minElement;
        maxElement = array[i] > maxElement ? array[i] : maxElement;
    }
    const int elementsRange = maxElement - minElement + 1;
    int* elementCounter = malloc(elementsRange * sizeof(int));
    for (int k = 0; k < elementsRange; ++k) {
        elementCounter[k] = 0;
    }
    for (int j = 0; j < arraySize; ++j) {
        ++elementCounter[array[j] - minElement];
    }
    int result = 0, maxAmount = 0;
    for (int h = 0; h < elementsRange; ++h) {
        if (maxAmount < elementCounter[h]) {
            result = h + minElement;
            maxAmount = elementCounter[h];
        }
    }
    free(elementCounter);
    return result;
}

bool test() {
    int testArray[] = { -5, -5, 10, 10, 10, 10, 10, 10, -10, 5, 5, 5, 10, 10 };
    const int testArraySize = sizeof(testArray) / sizeof(int);
    int errorCode = 0;
    return commonestElement(testArray, testArraySize, &errorCode) == 10 && !errorCode;
}

int main(void) {
    printf("Enter array size\n");
    int arraySize = 0;
    scanf("%d", &arraySize);
    int *array = malloc(sizeof(int) * arraySize);
    for (int i = 0; i < arraySize; ++i) {
        array[i] = rand() % 20000 - 10000;
        //printf("%d\t", array[i]);
    }
    const clock_t startTime = clock();
    int errorCode = 0;
    int result = commonestElement(array, arraySize, &errorCode);
    const double duration = (double)(clock() - startTime) / CLOCKS_PER_SEC;
    printf("\nCommonest element = %d\n", result);
    printf("Duration: %lf", duration);
    free(array);
}
