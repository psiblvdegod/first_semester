#include <stdio.h>
#include <stdlib.h>
#define ARRAY_SIZE 30

int swap(int* left, int* right) {
    *left = *left + *right;
    *right = *left - *right;
    *left = *left - *right;
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

int main(void) {
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
