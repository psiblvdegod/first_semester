#include "fileProcessing.h"
#include "errorCode.h"
#include "tests.h"

bool floatComparison(double first, double second) {
    const double epsilon = 0.00001;
    first = first > 0 ? first : -1.0 * first;
    second = second > 0 ? second : -1.0 * second;
    const double difference = first > second ? first - second : second - first;
    return difference < epsilon;
}

int hashTableTests() {
    int errorCode = NO_ERRORS;
    const size_t hashTableSize = 1;
    HashTable *hashTable = createHashTable(hashTableSize, &errorCode);
    addWordToHashTable(&hashTable, "1", &errorCode);
    addWordToHashTable(&hashTable, "2", &errorCode);
    addWordToHashTable(&hashTable, "2", &errorCode);
    addWordToHashTable(&hashTable, "3", &errorCode);
    addWordToHashTable(&hashTable, "3", &errorCode);
    addWordToHashTable(&hashTable, "3", &errorCode);
    const bool findTest = findFrequency(hashTable, "2", &errorCode) == 2;
    deleteHashTable(&hashTable, &errorCode);
    if (errorCode == NO_ERRORS && !findTest) {
        return -1;
    }
    return errorCode;
}

int hashTableFileTest() {
    int errorCode = NO_ERRORS;
    const int hashTableSize = 10;
    HashTable *hashTable = getFrequenciesFromFile(hashTableSize, "../text.txt", &errorCode);
    if (errorCode != NO_ERRORS) {
        deleteHashTable(&hashTable, &errorCode);
        return errorCode;
    }
    const bool calculateTest1 = floatComparison(calculateFillFactor(hashTable, &errorCode), 0.8);
    if (errorCode != NO_ERRORS) {
        deleteHashTable(&hashTable, &errorCode);
        return errorCode;
    }
    const bool calculateTest2 = floatComparison(calculateAverageListLength(hashTable, &errorCode), 1.6);
    if (errorCode != NO_ERRORS) {
        deleteHashTable(&hashTable, &errorCode);
        return errorCode;
    }
    const bool calculateTest3 = findMaxListLength(hashTable, &errorCode) == 2;
    if (errorCode != NO_ERRORS) {
        deleteHashTable(&hashTable, &errorCode);
        return errorCode;
    }
    const bool test = calculateTest1 && calculateTest2 && calculateTest3;
    if (errorCode == NO_ERRORS && !test) {
        return -1;
    }
    return errorCode;
}

