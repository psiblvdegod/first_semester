#include "search.h"
#include "sorting.h"
#include <stdlib.h>
#include <stdio.h>

bool binarySearch(const int array[], const int arraySize, const int target) {
    int left = 0, right = arraySize - 1;
    while (left < right) {
        const int central = left + (right - left) /2;
        if (array[central] == target) {
            return true;
        }
        else if (array[central] < target) {
            left = central + 1;
        }
        else if (array[central] > target) {
            right = central - 1;
        }
    }
    return false;
}

void search(int array[], const int n, const int k, bool *errorCode) {
    if (n < 1 || k < 1) {
        *errorCode = true;
        return;
    }
    smartQsort(array, 0, n, errorCode);
    if (*errorCode) {
        return;
    }
    for (int j = 0; j < k; ++j) {
        const int target = rand() % 20000 - 10000;
        const bool result = binarySearch(array, n, target);
        printf("%d is%sin array\n", target, result ? " " : " not ");
    }
}
