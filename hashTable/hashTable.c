#include "hashTable.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int hashFunction(const int hashTableSize, Key key) {
    if (hashTableSize < 1 || key == NULL) {
        return 0;
    }
    int result = 1;
    for (int i = 0; key[i] != '\0'; ++i) {
        result = (result + ((unsigned char) key[i]) * (i + 1)) % hashTableSize;
    }
    return result;
}

HashTable createHashTable(const int hashTableSize, bool * errorCode) {
    if (hashTableSize <= 0) {
        *errorCode = true;
        return NULL;
    }
    HashTable hashTable = calloc(hashTableSize, sizeof(List));
    if (hashTable == NULL) {
        *errorCode = true;
    }
    return hashTable;
}

void updateHashTable(HashTable hashTable, const int hashTableSize, Key key, bool * errorCode) {
    if (hashTable == NULL || hashTableSize <= 0) {
        *errorCode = true;
        return;
    }
    const int hash = hashFunction(hashTableSize, key);
    hashTable[hash] = updateList(hashTable[hash], key, 1, errorCode);
}

int countElementsAmount(HashTable hashTable, const int hashTableSize, bool * errorCode) {
    if (hashTable == NULL || hashTableSize <= 0) {
        *errorCode = true;
        return -1;
    }
    int result = 0;
    for (int i = 0; i < hashTableSize; ++i) {
        List tableElement = hashTable[i];
        while (tableElement != NULL) {
            ++result;
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
        List tableElement = hashTable[i];
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
    const int elementsAmount = countElementsAmount(hashTable, hashTableSize, errorCode);
    for (int i = 0; i < hashTableSize; ++i) {
        if (hashTable[i] != NULL) {
            ++amountOfNotEmptyCells;
        }
    }
    return ((double) elementsAmount) / ((double) amountOfNotEmptyCells);
}

double calculateFillFactor(HashTable hashTable, const int hashTableSize, bool * errorCode) {
    if (hashTable == NULL || hashTableSize <= 0) {
        *errorCode = true;
        return -1;
    }
    const int elementsAmount = countElementsAmount(hashTable, hashTableSize, errorCode);
    return ((double) elementsAmount) / ((double) hashTableSize);
}

int findFrequencyByKey(HashTable hashTable, const int hashTableSize, Key key, bool * errorCode) {
    if (hashTable == NULL) {
        *errorCode = true;
        return -1;
    }
    const int hash = hashFunction(hashTableSize, key);
    List list = hashTable[hash];
    while (list != NULL) {
        if (strcmp(key, getKey(list, errorCode)) == 0) {
            return getFrequency(list, errorCode);
        }
        list = getPrevious(list);
    }
    return 0;
}

HashTable expandHashTable(HashTable hashTable, const int hashTableSize, bool * errorCode) {
    if (hashTable == NULL || hashTableSize < 0) {
        *errorCode = true;
        return hashTable;
    }
    const double fillFactor = calculateFillFactor(hashTable, hashTableSize, errorCode);
    if (fillFactor < 2) {
        return hashTable;
    }
    const int newSize = (int)(fillFactor * hashTableSize * 2);
    HashTable newHashTable = createHashTable(newSize, errorCode);
    if (*errorCode) {
        return hashTable;
    }
    for (int i = 0; i < hashTableSize; ++i) {
        while (hashTable[i] != NULL) {
            const int hash = hashFunction(hashTableSize, getKey(hashTable[i], errorCode));
            Key key = getKey(hashTable[i], errorCode);
            Value frequency = getFrequency(hashTable[i], errorCode);
            newHashTable[hash] = updateList(newHashTable[hash], key, frequency, errorCode);
            hashTable[i] = getPrevious(hashTable[i]);
        }
    }
    //free(hashTable);
    return newHashTable;
}

void printFrequencies(HashTable hashTable, const int hashTableSize, bool * errorCode) {
    if (hashTable == NULL) {
        *errorCode = true;
        return;
    }
    for (int i = 0; i < hashTableSize; ++i) {
        List tableElement = hashTable[i];
        while (tableElement != NULL) {
            printf("%s - %d\n", getKey(tableElement, errorCode), getFrequency(tableElement, errorCode));
            tableElement = getPrevious(tableElement);
        }
    }
}