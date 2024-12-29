#include "fileProcessing.h"
#include "errorCode.h"
#include "tests.h"

bool floatComparison(double first, double second) {
    first = first > 0 ? first : -first;
    second = second > 0 ? second : -second;
    double difference = first > second ? first - second : second - first;
    return difference < 0.00001;
}

int hashTableTests() {
    int errorCode = NO_ERRORS;
    const int hashTableSize = 10;
    HashTable *hashTable = createHashTable(hashTableSize, &errorCode);
    updateHashTable(hashTable, "ggg", &errorCode);
    updateHashTable(hashTable, "ggg", &errorCode);
    updateHashTable(hashTable, "ggg", &errorCode);
    updateHashTable(hashTable, "ggg", &errorCode);
    updateHashTable(hashTable, "ggg", &errorCode);
    updateHashTable(hashTable, "0", &errorCode);
    updateHashTable(hashTable, "01", &errorCode);
    const bool test1 = findFrequency(hashTable, "555", &errorCode) == 5;
    return test1;
}

int hashTableFileTest() {
    int errorCode = NO_ERRORS;
    const int hashTableSize = 10;
    HashTable *hashTable = getFrequenciesFromFile(hashTableSize, "../text.txt", &errorCode);
    if (errorCode != NO_ERRORS) {
        deleteHashTable(&hashTable, &errorCode);
        return errorCode;
    }
    const bool findTest1 = findFrequency(hashTable, "222", &errorCode) == 2;
    expandHashTable(&hashTable, &errorCode);
    if (errorCode != NO_ERRORS) {
        deleteHashTable(&hashTable, &errorCode);
        return errorCode;
    }
    const bool findTest2 = findFrequency(hashTable, "888", &errorCode) == 8;
    const bool findTest3 = findFrequency(hashTable, "", &errorCode) == 0;
    const bool countTest = countElementsAmount(hashTable, &errorCode) == 8;
    const bool calculateTest1 = floatComparison(calculateFillFactor(hashTable, &errorCode), 0.8);
    const bool calculateTest2 = floatComparison(calculateAverageListLength(hashTable, &errorCode), 1.6);
    const bool calculateTest3 = calculateMaxListLength(hashTable, &errorCode) == 2;
    const bool test = findTest1 && findTest2 && findTest3 && calculateTest1 && calculateTest2 && calculateTest3;
    if (errorCode == NO_ERRORS && !test) {
        return -1;
    }
    return errorCode;
}

