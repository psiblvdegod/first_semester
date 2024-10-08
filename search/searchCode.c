#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void insertionSort(int* array, int left, int right) {
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

void smartQsort(int* array, int leftEdge, int rightEdge) {
    if (rightEdge - leftEdge <= 10) {
        insertionSort(array, leftEdge, rightEdge);
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
        smartQsort(array, leftEdge, right);
        smartQsort(array, left, rightEdge);
    }
}


bool insertionSortTest() {
    int array[] = { 5, 3, 4, 1, 6, 8, 7, 9, 0, 2 };
    insertionSort(array, 0, 10);
    for (int k = 1; k < 10; ++k) {
        if (array[k] < array[k - 1]) {
            return false;
        }
    }
    return true;
}

bool smartQsortTest() {
    int array[] = { -10, 20, 30, 40, -30, -40, -20, 10, 50, -50, 0, -20 };
    smartQsort(array, 0, 11);
    for (int i = 1; i < 12; ++i) {
        if (array[i] < array[i - 1]) {
            return false;
        }
    }
    return true;
}

void test(int array[]) {
    printf("%d", sizeof(array) / sizeof(int));
}

int main(void) {
    if (!smartQsortTest || !insertionSortTest) {
        printf("Error. Tests failed.\n");
        return 0;
    }
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    test(a);
}
