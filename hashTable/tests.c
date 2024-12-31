#include "fileProcessing.h"
#include "errorCode.h"
#include "tests.h"

int hashTableTests() {
    int errorCode = NO_ERRORS;
    HashTable *hashTable = createHashTable(&errorCode);
    addWordToHashTable(&hashTable, "1", &errorCode);
    addWordToHashTable(&hashTable, "2", &errorCode);
    addWordToHashTable(&hashTable, "2", &errorCode);
    addWordToHashTable(&hashTable, "3", &errorCode);
    addWordToHashTable(&hashTable, "3", &errorCode);
    addWordToHashTable(&hashTable, "3", &errorCode);
    const bool findTest = findFrequency(hashTable, "2", &errorCode) == 2;
    deleteHashTable(&hashTable, &errorCode);
    if (errorCode == NO_ERRORS && !findTest) {
        return TESTS_FAILED_ERROR;
    }
    return errorCode;
}

int hashTableFileTest() {
    int errorCode = NO_ERRORS;
    HashTable *hashTable = getFrequenciesFromFile("../text.txt", &errorCode);
    const bool test1 = findFrequency(hashTable, "777", &errorCode) == 7;
    const bool test2 = findFrequency(hashTable, "", &errorCode) == 0;
    const bool test = test1 && test2;
    deleteHashTable(&hashTable, &errorCode);
    if (errorCode == NO_ERRORS && !test) {
        return TESTS_FAILED_ERROR;
    }
    return errorCode;
}

