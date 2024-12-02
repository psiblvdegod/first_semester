#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "sorting.h"
#include "tests.h"

int main(void) {
    if (!smartQsortTest() || !insertionSortTest()) {
        printf("Error. Test failed.\n");
        return -1;
    }
    int array[1001] = {0};
    srand(666);
    for (int i = 0; i < 1000; ++i) {
        array[i] = rand() % 2000 - 1000;
    }
    bool errorCode = false;
    smartQsort(array, 0, 1000, &errorCode);
    if (errorCode) {
        printf("Something went wrong.\n");
        return -1;
    }
    printf("Sorted random array.\n");
    for (int k = 0; k < 1000; ++k) {
        printf("%d ", array[k]);
    }
}
