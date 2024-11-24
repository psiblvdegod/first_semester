#include "tests.h"

bool bubbleSortTest() {
    int array[] = {5, 4, 2, 1, 3};
    bubbleSort(array, 5);
    for (int i = 0; i < 5; ++i) {
        if (array[i] != i + 1) {
            return false;
        }
    }
    return true;
}

bool countingSortTest() {
    bool errorCode = false;
    int array[] = {-20, 10, 15, -30, 40, -30, -20, 10, 40, -20};
    countingSort(array, 10, &errorCode);
    for (int i = 1; i < 10; ++i) {
        if (array[i - 1] > array[i]) {
            return false;
        }
    }
    return true;
}
