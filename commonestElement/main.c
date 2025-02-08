#include "commonestElement.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int main(void) {
    if (!test()) {
        printf("Error. Test failed.\n");
        return -1;
    }
    int array[1000] = {0};
    const int arraySize = sizeof(array) / sizeof(int);
    for (int i = 0; i < arraySize; ++i) {
        array[i] = rand() % 100;
    }
    const clock_t startTime = clock();
    bool errorCode = false;
    const int result = findCommonestElement(array, arraySize, &errorCode);
    const double duration = (double)(clock() - startTime) / CLOCKS_PER_SEC;
    if (errorCode) {
        printf("Something went wrong.\n");
        return -1;
    }
    printf("Array size: %d\n", arraySize);
    printf("Commonest element = %d\n", result);
    printf("Duration: %lf", duration);
}