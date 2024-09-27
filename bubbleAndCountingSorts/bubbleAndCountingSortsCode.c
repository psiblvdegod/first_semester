#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define ELEMENTS_RANGE 100000
#define ARRAY_SIZE 100000

void swap(int *left, int *right) { 
    *left = *left + *right; 
    *right = *left - *right; 
    *left = *left - *right; 
} 

int* bubbleSort(int array[], int arraySize) {
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

int* countingSort(int array[], int arraySize) {
    int *amountOfElements = malloc((ELEMENTS_RANGE) * sizeof(int));
    for (int i = 0; i < ELEMENTS_RANGE; ++i) {
        amountOfElements[i] = 0;
    }
    for (int k = 0; k < arraySize; ++k) {
        amountOfElements[array[k]] += 1;
    }
    int index = 0;
    for (int q = 0; q < ELEMENTS_RANGE; ++q) {
        for (int w = 0; w < amountOfElements[q]; ++w) {
            array[index] = q;
            index += 1;
        }
    }
    free(amountOfElements);
    return array;
}

bool bubbleSortTest() {
    int unsortedArray[] = {5, 4, 2 ,1 ,3};
    int *sortedArray = bubbleSort(unsortedArray, 5);
    for (int i = 0; i < 5; ++i) {
        if (sortedArray[i] != i + 1){
            return false;
        }
    }
    return true;
}

bool countingSortTest() {
    int unsortedArray[] = {10, 30, 50, 3 ,10 ,23, 6, 77, 9, 28};
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
        unsortedArray1[i] = rand() % ELEMENTS_RANGE;
        unsortedArray2[i] = rand() % ELEMENTS_RANGE;
    }
    clock_t startTime = clock();
    countingSort(unsortedArray1, ARRAY_SIZE);
    double countingSortDuration = (double) (clock() - startTime) / CLOCKS_PER_SEC;
    startTime = clock();
    bubbleSort(unsortedArray2, ARRAY_SIZE);
    double bubbleSortDuration = (double) (clock() - startTime) / CLOCKS_PER_SEC;
    printf("Counting sort duration = %lf\nBubble sort duration = %lf\nCounting sort is %.0lf faster.\n", countingSortDuration, bubbleSortDuration, bubbleSortDuration / countingSortDuration);
}
