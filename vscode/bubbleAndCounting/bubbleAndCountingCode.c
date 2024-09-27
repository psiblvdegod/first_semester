#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define ARRAY_SIZE 100000

void swap(int *left, int *right) {
    *left = *left + *right;
    *right = *left - *right;
    *left = *left - *right;
}

int *bubbleSort(int array[], int arraySize) {
    int swapFlag = 0;
    while (true) {
        swapFlag = 0;
        for (int i = 1; i < arraySize; ++i) {
            if (array[i] < array[i - 1]) {
                swapFlag = 1;
                swap(&array[i], &array[i - 1]);
            }
        }
        if (swapFlag == 0) {
            return array;
        }
    }
}

int *countingSort(int array[], int arraySize) {
    int maxElement = 0, minElement = 0;
    for (int j = 0; j < arraySize; ++j) {
        maxElement = ((array[j] > maxElement) ? (array[j]) : (maxElement));
        minElement = ((array[j] < minElement) ? (array[j]) : (minElement));
    }
    const int elementsRange = maxElement - minElement + 1;
    int *amountOfElements = malloc((elementsRange) * sizeof(int));
    for (int i = 0; i < elementsRange; ++i) {
        amountOfElements[i] = 0;
    }
    for (int k = 0; k < arraySize; ++k) {
        ++amountOfElements[array[k] - minElement];
    }
    int index = 0;
    for (int q = 0; q < elementsRange; ++q) {
        for (int w = 0; w < amountOfElements[q]; ++w) {
            array[index] = q + minElement;
            ++index;
        }
    }
    free(amountOfElements);
    return array;
}

bool bubbleSortTest() {
    int unsortedArray[] = {5, 4, 2, 1, 3};
    int *sortedArray = bubbleSort(unsortedArray, 5);
    for (int i = 0; i < 5; ++i) {
        if (sortedArray[i] != i + 1) {
            return false;
        }
    }
    return true;
}

bool countingSortTest() {
    int unsortedArray[] = {-20, 10, 15, -30, 40, -30, -20, 10, 40, -20};
    int *sortedArray = countingSort(unsortedArray, 10);
    for (int i = 1; i < 10; ++i) {
        if (sortedArray[i - 1] > sortedArray[i]) {
            return false;
        }
    }
    return true;
}

int main(void) {
    const bool test = bubbleSortTest() && countingSortTest();
    if (!test) {
        printf("Error. Tests failed.\n");
        return -1;
    }
    int unsortedArray1[ARRAY_SIZE] = {0};
    int unsortedArray2[ARRAY_SIZE] = {0};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        unsortedArray1[i] = rand() % ARRAY_SIZE - (ARRAY_SIZE / 2);
        unsortedArray2[i] = rand() % ARRAY_SIZE - (ARRAY_SIZE / 2);
    }
    clock_t startTime = clock();
    countingSort(unsortedArray1, ARRAY_SIZE);
    double countingSortDuration = (double)(clock() - startTime) / CLOCKS_PER_SEC;
    startTime = clock();
    bubbleSort(unsortedArray2, ARRAY_SIZE);
    double bubbleSortDuration = (double)(clock() - startTime) / CLOCKS_PER_SEC;
    printf("Counting sort duration = %lf\nBubble sort duration = %lf\nCounting sort is %.0lf faster.\n", countingSortDuration, bubbleSortDuration, bubbleSortDuration / countingSortDuration);
}