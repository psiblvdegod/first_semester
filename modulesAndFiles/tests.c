#include "tests.h"
#include <string.h>

bool hashTableTest() {
    bool errorCode = false;
    HashTable hashTable = createHashTable(20, &errorCode);
    if (errorCode) {
        return false;
    }
    updateHashTable(hashTable, "123", &errorCode);
    updateHashTable(hashTable, "123", &errorCode);
    updateHashTable(hashTable, "345", &errorCode);
    updateHashTable(hashTable, "123", &errorCode);
    updateHashTable(hashTable, "657", &errorCode);
    const bool findTest = strcmp(findCommonestElement(hashTable, &errorCode), "123") == 0;
    return findTest && !errorCode;
}