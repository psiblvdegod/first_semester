#include "hashTable.h"
#include <string.h>
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
    int amountOfNotEmptyCells = 0;
    int cellsLength = 0;
    for (int i = 0; i < hashTableSize; ++i) {
        if (hashTable[i] != NULL) {
            ++amountOfNotEmptyCells;
            List * tableElement = hashTable[i];
            while (tableElement != NULL) {
                ++cellsLength;
                tableElement = getPrevious(tableElement);
            }
        }
    }
    return ((double) cellsLength) / ((double) amountOfNotEmptyCells);
}

double calculateFillFactor(HashTable hashTable, const int hashTableSize, bool * errorCode) {
    if (hashTable == NULL || hashTableSize <= 0) {
        *errorCode = true;
        return -1;
    }
    const int amountOfElements = countElementsAmount(hashTable, hashTableSize, errorCode);
    int amountOfCells = 0;
    for (int i = 0; i < hashTableSize; ++i) {
        ++amountOfCells;
    }
    return ((double) amountOfElements) / ((double) amountOfCells);
}

int findFrequencyByKey(HashTable hashTable, const int hashTableSize, Key key, bool * errorCode) {
    if (hashTable == NULL) {
        *errorCode = true;
        return -1;
    }
    const int hash = hashFunction(hashTableSize, key);
    List * list = hashTable[hash];
    while (list != NULL) {
        if (strcmp(key, getKey(list, errorCode)) == 0) {
            return getFrequency(list, errorCode);
        }
        list = getPrevious(list);
    }
    return 0;
}