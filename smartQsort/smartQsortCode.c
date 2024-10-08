#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void insertionSort(int* array, int left, int right, int *errorCode) {
    if (left < 0 || right < -1 || right - left < -1) {
        *errorCode = 1;
        return 0;
    }
    for (int i = left + 1; i < right; ++i) {
        for (int j = i; j > left; --j) {
            if (array[j] < array[j - 1]) {
                int temp = array[j];
                array[j] = array[j - 1];
                array[j - 1] = temp;
            }
            else {
                break;
            }
        }
    }
}

void smartQsort(int* array, int leftEdge, int rightEdge, int *errorCode) {
    if (leftEdge < 0 || rightEdge < -1 || rightEdge - leftEdge < -1) {
        *errorCode = 1;
        return 0;
    }
    if (rightEdge - leftEdge <= 10) {
        insertionSort(array, leftEdge, rightEdge, errorCode);
    }
    if (leftEdge < rightEdge) {
        int left = leftEdge, right = rightEdge;
        int pivot = array[(left + right) / 2];
        while (left < right) {
            while (array[left] < pivot) {
                ++left;
            }
            while (array[right] > pivot) {
                --right;
            }
            if (left <= right) {
                int temp = array[left];
                array[left] = array[right];
                array[right] = temp;
                ++left;
                --right;
            }
        }
        smartQsort(array, leftEdge, right, errorCode);
        smartQsort(array, left, rightEdge, errorCode);
    }
}

bool insertionSortTest() {
    int array[] = { 5, 3, 4, 1, 6, 8, 7, 9, 0, 2 };
    int errorCode = 0;
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
    int errorCode = 0;
    smartQsort(array, 0, 11, &errorCode);
    for (int i = 0; i < 12; ++i) {
        if (array[i] < array[i - 1]) {
            return false;
        }
    }
    return !errorCode;
}

int main(void) {
    if (!smartQsortTest() || !insertionSortTest) {
        printf("Error. Test failed.\n");
        return 0;
    }
    int array[1001] = {0};
    for (int i = 0; i < 1000; ++i) {
        array[i] = rand() % 2000 - 1000;
    }
    int errorCode = 0 ;
    smartQsort(array, 0, 1000, &errorCode);
    if (errorCode) {
        printf("Error. Invalid value.\n");
        return 0;
    }
    printf("Sorted random array.\n\n");
    for (int k = 0; k < 1000; ++k) {
        printf("%d\t", array[k]);
    }
}
