#include "tests.h"
#include <string.h>

#define NO_ERRORS 0
#define MEMORY_ALLOCATION_ERROR 44
#define INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION 1
#define FILE_OPENING_ERROR 15
#define TESTS_FAILED_ERROR (-1)

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
