#include "sorting.h"
#include "tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define ARRAY_SIZE 100000

int main(void) {
    if (!bubbleSortTest() || !countingSortTest()) {
        printf("Error. Tests failed.\n");
        return -1;
    }
    int array1[ARRAY_SIZE] = {0};
    int array2[ARRAY_SIZE] = {0};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        array1[i] = rand() % ARRAY_SIZE - (ARRAY_SIZE / 2);
        array2[i] = rand() % ARRAY_SIZE - (ARRAY_SIZE / 2);
    }
    bool errorCode = false;
    clock_t startTime = clock();
    countingSort(array1, ARRAY_SIZE, &errorCode);
    const double countingSortDuration = (double)(clock() - startTime) / CLOCKS_PER_SEC;
    if (errorCode) {
        printf("Memory allocation error.\n");
        return -1;
    }
    startTime = clock();
    bubbleSort(array2, ARRAY_SIZE);
    const double bubbleSortDuration = (double)(clock() - startTime) / CLOCKS_PER_SEC;
    printf("Counting sort duration = %lf\nBubble sort duration = %lf\n", countingSortDuration, bubbleSortDuration);
    printf("Counting sort is %.0lf times faster.\n", bubbleSortDuration / countingSortDuration);
}