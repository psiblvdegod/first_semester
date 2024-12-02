#include "tests.h"

bool insertionSortTest() {
    int array[] = { 5, 3, 4, 1, 6, 8, 7, 9, 0, 2 };
    bool errorCode = false;
    insertionSort(array, 0, 10, &errorCode);
    for (int k = 1; k < 10; ++k) {
        if (array[k] < array[k - 1]) {
            return false;
        }
    }
    return !errorCode;
}

bool smartQsortTest() {
    int array[] = { -10, 20, 50, -60, -40, 30, 40, -30, 60, -20, -50, 10 };
    bool errorCode = false;
    smartQsort(array, 0, 11, &errorCode);
    for (int i = 1; i < 12; ++i) {
        if (array[i] < array[i - 1]) {
            return false;
        }
    }
    return !errorCode;
}