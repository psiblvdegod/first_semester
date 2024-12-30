#include "fileProcessing.h"
#include "hashTable.h"
#include "errorCode.h"
#include "tests.h"
#include <stdio.h>

int main(void) {
    int errorCode = hashTableTests();
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    errorCode = hashTableFileTest();
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    const size_t hashTableSize = 10;
    HashTable *hashTable = getFrequenciesFromFile(hashTableSize, "../text.txt", &errorCode);
    const double fillFactor = calculateFillFactor(hashTable, &errorCode);
    const size_t maxListLength = findMaxListLength(hashTable, &errorCode);
    const double averageListLength = calculateAverageListLength(hashTable, &errorCode);
    printf("fill factor: %.2lf\n", fillFactor);
    printf("max list length: %zu\n", maxListLength);
    printf("fill factor: %.2lf\n", averageListLength);
    return errorCode;
}