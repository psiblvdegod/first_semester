#include "tests.h"
#include "errorCode.h"
#include <string.h>

int hashTableTests() {
    int errorCode = NO_ERRORS;
    HashTable *hashTable = createHashTable(10, &errorCode);
    updateHashTable(hashTable, "ggg", &errorCode);
    updateHashTable(hashTable, "ggg", &errorCode);
    updateHashTable(hashTable, "ggg", &errorCode);
    updateHashTable(hashTable, "ggg", &errorCode);
    updateHashTable(hashTable, "ggg", &errorCode);
    updateHashTable(hashTable, "0", &errorCode);
    updateHashTable(hashTable, "01", &errorCode);
    int bp1 = 0;
}
/*
void hashTableFileTest(int *errorCode) {
    const int hashTableSize = 100;
    HashTable hashTable = createHashTable(hashTableSize, errorCode);
    if (*errorCode != NO_ERRORS) {
        deleteHashTable(hashTable, errorCode);
        return;
    }
    const char *path = "../text.txt";
    fillHashTable(hashTable, hashTableSize, path, errorCode);
    if (*errorCode != NO_ERRORS) {
        deleteHashTable(hashTable, errorCode);
        return;
    }
    hashTable = expandHashTable(hashTable, &hashTableSize, errorCode);
    if (*errorCode != NO_ERRORS) {
        deleteHashTable(hashTable, errorCode);
        return;
    }
    const bool test = findFrequencyByKey(hashTable, hashTableSize, key, errorCode);
    const bool test = calculateFillFactor(hashTable, hashTableSize, errorCode);
    const bool test = calculateAverageListLength(hashTable, hashTableSize, errorCode);
    const bool test = calculateMaxListLength(hashTable, hashTableSize, errorCode);
}
 */
