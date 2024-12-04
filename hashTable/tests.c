#include "tests.h"
#include <string.h>

bool listTests() {
    bool errorCode = false;
    List list = createListElement(NULL, "123", 5, &errorCode);
    list = createListElement(list, "234", 10, &errorCode);
    list = createListElement(list, "456", 4, &errorCode);
    list = createListElement(list, "567", 10, &errorCode);
    updateList(list, "567", 5, &errorCode);
    const bool test1 = strcmp(getKey(getPrevious(list), &errorCode), "456") == 0;
    const bool test2 = getFrequency(list, &errorCode) == 15;
    return test1 && test2 && !errorCode;
}

bool hashTableTests() {
    bool errorCode = false;
    const int hashTableSize = 2;
    HashTable hashTable = createHashTable(hashTableSize, &errorCode);
    if (errorCode) {
        return false;
    }
    Key keys[] = {"123", "321", "213", "123", "45", "54", "123", "213", "99", "122"};
    for (int i = 0; i < 8 ; ++i) {
        updateHashTable(hashTable, hashTableSize, keys[i], &errorCode);
    }
    const double fillFactor = calculateFillFactor(hashTable, hashTableSize, &errorCode);
    const double averageListLength = calculateAverageListLength(hashTable, hashTableSize, &errorCode);
    const int maxListLength = calculateMaxListLength(hashTable, hashTableSize, &errorCode);
    const bool test1 = findFrequencyByKey(hashTable, hashTableSize, "123", &errorCode) == 3;
    const bool test2 = fillFactor == 2.5;
    const bool test3 = averageListLength <= maxListLength;
    return test1 && test2 && test3 && !errorCode;
}
