#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int* array, int left, int right, int* errorCode) {
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

void smartQsort(int* array, int leftEdge, int rightEdge, int* errorCode) {
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

int search(int array[], int n, int k, int *errorCode) {
    if (n < 1 || k < 1) {
        *errorCode = 1;
        return 0;
    }
    smartQsort(array, 0, n, errorCode);
    if (*errorCode) {
        return 0;
    }
    int temp = 0;
    for (int j = 0; j < k; ++j) {
        temp = rand() % 20000 - 10000;
        for (int h = 0; h < n; ++h) {
            if (array[h] > temp) {
                printf("k = %d is NOT in array.\n", temp);
                break;
            }
            if (array[h] == temp) {
                printf("k = %d is in array.\n", temp);
                break;
            }
        }
    }
}

int main(void) {
    if (!smartQsortTest() || !insertionSortTest) {
        printf("Error. Test failed.\n");
        return 0;
    }
    int n = 0, k = 0;
    printf("Enter n, k\n");
    scanf("%d%d", &n, &k);
    int* array = malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        array[i] = rand() % 20000 - 10000;
    }
    int errorCode = 0;
    const clock_t startTime = clock();
    search(array, n, k, &errorCode);
    double duration = (double)(clock() - startTime) / CLOCKS_PER_SEC;
    if (errorCode) {
        printf("Error. Invalid value.\n");
        return 0;
    }
    printf("Algorithm duration = %lf.", duration);
}