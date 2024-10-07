#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ARRAY_SIZE 100

void swap(int* left, int* right) {
    *left = *left + *right;
    *right = *left - *right;
    *left = *left - *right;
}

bool swapTest() {
    int left = 100, right = -1000;
    swap(&left, &right);
    return left == -1000 && right == 100;
}

int* semiQsort(int array[], int arrayLength) {
    int left = 0, right = arrayLength - 1;
    int fulcrum = array[0];
    while (left <= right) {
        while (array[left] < fulcrum) {
            left += 1;
        }
        while (array[right] >= fulcrum) {
            right -= 1;
        }
        if (left <= right) {
            swap(&array[left], &array[right]);
            left += 1;
            right -= 1;
        }
    }
    return array;
}

bool semiQsortTest() {
    int array1[] = {1, 0, 0, 1};
    int array2[] = {1, 0, 0, 0, 1};
    semiQsort(array1, 4);
    semiQsort(array2, 5);
    int sortedArray1[] = {0, 0, 1, 1};
    int sortedArray2[] = {0, 0, 0, 1, 1};
    for (int i = 0; i < 4; ++i) {
        if (array1[i] != sortedArray1[i] || array2[i] != sortedArray2[i]) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    bool test = semiQsortTest() & swapTest();
    if (!test) {
        printf("Error. Tests failed.\n");
    }
    else {
        int randomArray[ARRAY_SIZE];
        for (int i = 0; i < ARRAY_SIZE; ++i) {
            randomArray[i] = rand() % 101;
        }
        printf("First element: %d\nArray: ", randomArray[0]);
        int* result = semiQsort(randomArray, ARRAY_SIZE);
        for (int i = 0; i < ARRAY_SIZE; ++i) {
            printf("%d ", *(result + i));
        }
    }
}
