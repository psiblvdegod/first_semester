#include "test.h"
#include "sorting.h"
#include "tree.h"

int main(void) {
    if (!treeSortTests() || !treeTests()) {
        return -1;
    }
    bool errorCode = false;
    Value array[] = {"135", "132", "23","2344" ,"3223", "5342", "12"};
    const int arraySize = sizeof(array) / sizeof(Value);
    treeSort(array, arraySize, &errorCode);
    if (errorCode) {
        printf("Something went wrong.\n");
        return -1;
    }
    printf("Sorted array:\n");
    for (int i = 0; i < arraySize; ++i) {
        printf("%s ", array[i]);
    }
}
