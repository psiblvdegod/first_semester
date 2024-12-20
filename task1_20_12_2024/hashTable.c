#include "hashTable.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct HashTable {
    Value *table;
    int size;
    int elementsAmount;
};

HashTable createHashTable(const int hashTableSize, bool * errorCode) {
    if (hashTableSize <= 0) {
        *errorCode = true;
        return NULL;
    }
    HashTable hashTable = calloc(hashTableSize, sizeof(const char*));
    if (hashTable == NULL) {
        *errorCode = true;
        return NULL;
    }
    hashTable->size = hashTableSize;
    return hashTable;
}

int hashFunction(HashTable hashTable, Key key) {
    if (hashTable->size < 1 || key == NULL) {
        return 0;
    }
    int result = 1;
    for (int i = 0; key[i] != '\0'; ++i) {
        result = (result + ((unsigned char) key[i]) * (i + 1)) % hashTable->size;
    }
    if (hashTable->table[result] == NULL) {
        return result;
    }
    for (int i = result; ; i == hashTable->size ? i = 0 : ++i) {
        if (hashTable->table[i] == NULL) {
            return i;
        }
    }
}

void insert(HashTable hashTable, Key key, bool *errorCode) {
    if (hashTable == NULL || hashTable->size == hashTable->elementsAmount) {
        *errorCode = true;
        return;
    }
    const int hash = hashFunction(hashTableSize, key);
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

HashTable expandHashTable(HashTable hashTable, int * hashTableSize, bool * errorCode) {
    if (hashTable == NULL || *hashTableSize < 0) {
        *errorCode = true;
        return hashTable;
    }
    const double fillFactor = calculateFillFactor(hashTable, *hashTableSize, errorCode);
    if (fillFactor < 2) {
        return hashTable;
    }
    const int newSize = (int)(fillFactor * (*hashTableSize) * 2);
    HashTable newHashTable = createHashTable(newSize, errorCode);
    if (*errorCode) {
        return hashTable;
    }
    for (int i = 0; i < *hashTableSize; ++i) {
        while (hashTable[i] != NULL) {
            const int hash = hashFunction(newSize, getKey(hashTable[i], errorCode));
            newHashTable[hash] = updateList(newHashTable[hash], getKey(hashTable[i], errorCode), getFrequency(hashTable[i], errorCode), errorCode);
            hashTable[i] = getPrevious(hashTable[i]);
        }
    }
    free(hashTable);
    *hashTableSize = newSize;
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