#include "hashTable.h"
#include <stdlib.h>

int hashFunction(const int hashTableSize, Key key) {
    int result = 1;
    for (int i = 0; key[i] != '\0'; ++i) {
        result = (result + (unsigned char) key[i]) % hashTableSize;
    }
    return result;
}

HashTable createHashTable(const int hashTableSize, bool * errorCode) {
    if (hashTableSize <= 0) {
        *errorCode = true;
        return NULL;
    }
    HashTable hashTable = calloc(hashTableSize, 24); //43X
    if (hashTable == NULL) {
        *errorCode = true;
        return NULL;
    }
    return hashTable;
}

void updateHashTableByKey(HashTable hashTable, const int hashTableSize, Key key, bool * errorCode) {
    if (hashTable == NULL || hashTableSize <= 0) {
        *errorCode = true;
        return;
    }
    const int hash = hashFunction(hashTableSize, key);
    hashTable[hash] = updateListByKey(hashTable[hash], key, errorCode);
}

int countElementsAmount(HashTable hashTable, const int hashTableSize, bool * errorCode) {
    if (hashTable == NULL || hashTableSize <= 0) {
        *errorCode = true;
        return -1;
    }
    int result = 0;
    for (int i = 0; i < hashTableSize; ++i) {
        List * tableElement = hashTable[i];
        while (tableElement != NULL) {
            result += getFrequency(tableElement, errorCode);
            tableElement = getPrevious(tableElement);
        }
    }
    return result;
}

int calculateMaxListLength(HashTable hashTable, const int hashTableSize, bool * errorCode) {
    if (hashTable == NULL || hashTableSize <= 0) {
        *errorCode = true;
        return -1;
    }
    int result = 0;
    for (int i = 0; i < hashTableSize; ++i) {
        List * tableElement = hashTable[i];
        int tableElementLength = 0;
        while (tableElement != NULL) {
            ++tableElementLength;
            tableElement = getPrevious(tableElement);
        }
        result = result > tableElementLength ? result : tableElementLength;
    }
    return result;
}

double calculateAverageListLength(HashTable hashTable, const int hashTableSize, bool * errorCode) {
    if (hashTable == NULL || hashTableSize <= 0) {
        *errorCode = true;
        return -1;
    }
    const int amountOfElements = countElementsAmount(hashTable, hashTableSize, errorCode);
    int amountOfNotEmptyCells = 0;
    for (int i = 0; i < hashTableSize; ++i) {
        if (hashTable[i] != NULL) {
            ++amountOfNotEmptyCells;
        }
    }
    return ((double) amountOfElements) / ((double) amountOfNotEmptyCells);
}

double calculateFillFactor(HashTable hashTable, const int hashTableSize, bool * errorCode) {
    if (hashTable == NULL || hashTableSize <= 0) {
        *errorCode = true;
        return -1;
    }
    const int amountOfElements = countElementsAmount(hashTable, hashTableSize, errorCode);
    int amountOfNotEmptyCells = 0;
    for (int i = 0; i < hashTableSize; ++i) {
        ++amountOfNotEmptyCells;
    }
    return ((double) amountOfElements) / ((double) amountOfNotEmptyCells);
}