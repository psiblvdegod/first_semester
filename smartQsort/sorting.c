#include "sorting.h"

void insertionSort(int * array, const int left, const int right, bool * errorCode) {
    if (left < -1 || right < -1 || right - left < -1) {
        *errorCode = true;
        return;
    }
    for (int i = left + 1; i < right; ++i) {
        for (int j = i; j > left; --j) {
            if (array[j] < array[j - 1]) {
                const int temp = array[j];
                array[j] = array[j - 1];
                array[j - 1] = temp;
            }
            else {
                break;
            }
        }
    }
}

void smartQsort(int * array, const int leftEdge, const int rightEdge, bool * errorCode) {
    if (leftEdge < -1 || rightEdge < -1 || rightEdge - leftEdge < -1) {
        *errorCode = true;
        return;
    }
    if (rightEdge - leftEdge <= 10) {
        insertionSort(array, leftEdge, rightEdge, errorCode);
    }
    if (leftEdge < rightEdge) {
        int leftIndex = leftEdge, rightIndex = rightEdge;
        const int pivot = array[(leftIndex + rightIndex) / 2];
        while (leftIndex < rightIndex) {
            while (array[leftIndex] < pivot) {
                ++leftIndex;
            }
            while (array[rightIndex] > pivot) {
                --rightIndex;
            }
            if (leftIndex <= rightIndex) {
                const int temp = array[leftIndex];
                array[leftIndex] = array[rightIndex];
                array[rightIndex] = temp;
                ++leftIndex;
                --rightIndex;
            }
        }
        smartQsort(array, leftEdge, rightIndex, errorCode);
        smartQsort(array, leftIndex, rightEdge, errorCode);
    }
}
