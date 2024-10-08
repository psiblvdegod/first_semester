#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define ARRAY_SIZE 1000000 //also defines range of elements

int commonestElement(int array[], int arraySize) {
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
    return result;
}

bool test() {
    int testArray[] = { -5, -5, 10, 10, 10, 10, 10, 10, -10, 5, 5, 5, 10, 10 };
    const int testArraySize = sizeof(testArray) / sizeof(int);
    return commonestElement(testArray, testArraySize) == 10;
}

int main(void) {
    int array[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = rand() % ARRAY_SIZE - (ARRAY_SIZE / 2);
        //printf("%d\n", array[i]);
    }
    const clock_t startTime = clock();
    int result = commonestElement(array, ARRAY_SIZE);
    const double duration = (double)(clock() - startTime) / CLOCKS_PER_SEC;
    printf("Commonest element = %d\n", result);
    printf("Elements range = (%d : %d)\nArray size = %d\nDuration = %lf\n", -ARRAY_SIZE / 2, ARRAY_SIZE / 2, ARRAY_SIZE, duration);
}
