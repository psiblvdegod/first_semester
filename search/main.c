#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "search.h"
#include "tests.h"

int main(void) {
    if (!smartQsortTest() || !insertionSortTest()) {
        printf("Error. Test failed.\n");
        return -1;
    }
    int n = 0, k = 0;
    printf("Enter n, k\n");
    const int inputValidation =  scanf("%d%d", &n, &k);
    if (inputValidation != 2) {
        printf("Invalid value.\n");
        return -1;
    }
    int* array = calloc(n, sizeof(int));
    if (array == NULL) {
        printf("Memory allocation error.\n");
        return -1;
    }
    for (int i = 0; i < n; ++i) {
        array[i] = rand() % 20000 - 10000;
    }
    bool errorCode = false;
    search(array, n, k, &errorCode);
    if (errorCode) {
        printf("Something went wrong.\n");
        return -1;
    }
    free(array);
}