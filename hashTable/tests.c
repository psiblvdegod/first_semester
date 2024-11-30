#include "tests.h"
#include <stdio.h>
#include <string.h>

bool listTests() {
    bool errorCode = false;
    List list = createListElement(NULL, "123", &errorCode);
    list = createListElement(list, "234", &errorCode);
    list = createListElement(list, "456", &errorCode);
    list = createListElement(list, "567", &errorCode);
    updateListByKey(list, "567", &errorCode);
    const bool test1 = strcmp(getKey(getPrevious(list), &errorCode), "456") == 0;
    const bool test2 = getFrequency(list, &errorCode) == 2;
    return test1 && test2 && !errorCode;
}

bool hashTableTests() {
    bool errorCode = false;
    const int hashTableSize = 2;
    HashTable hashTable = createHashTable(hashTableSize, &errorCode);
    if (errorCode) {
        return false;
    }
    Key keys[] = {"123", "321", "213", "123", "45", "54", "123", "213"};
    for (int i = 0; i < 8 ; ++i) {
        updateHashTableByKey(hashTable, hashTableSize, keys[i], &errorCode);
    }
    const double fillFactor = calculateFillFactor(hashTable, hashTableSize, &errorCode);
    const double averageListLength = calculateAverageListLength(hashTable, hashTableSize, &errorCode);
    const int maxListLength = calculateMaxListLength(hashTable, hashTableSize, &errorCode);
    const bool test1 = findFrequencyByKey(hashTable, hashTableSize, "123", &errorCode) == 3;
    const bool test2 = fillFactor == 4;
    const bool test3 = averageListLength == 2.5;
    const bool test4 = maxListLength == 3;
    return test1 && test2 && test3 && test4 && !errorCode;
}