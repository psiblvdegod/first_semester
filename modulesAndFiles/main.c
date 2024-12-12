#include <stdio.h>
#include <stdbool.h>
#include "hashTable.h"

int main(void) {
    bool errorCode = false;
    const int hashTableSize = 1000;
    HashTable hashTable = createHashTable(hashTableSize, &errorCode);
    if (hashTable == NULL) {
        printf("Memory allocation error.\n");
        return -1;
    }
    FILE * file = fopen("../text.txt", "r");
    if (file == NULL) {
        printf("File opening error.\n");
        return -1;
    }
    fillHashTable(hashTable, file, &errorCode);
    const char * result = findCommonestElement(hashTable, &errorCode);
    if (errorCode || result == NULL) {
        printf("Something went wrong.\n");
        return -1;
    }
    printf("result: %s", result);
}
