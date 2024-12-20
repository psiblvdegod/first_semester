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

int hashFunction(HashTable hashTable, Value key) {
    int result = 1;
    for (int i = 0; key[i] != '\0'; ++i) {
        result = (result + ((unsigned char) key[i]) * (i + 1)) % hashTable->size;
    }
    return result;
}

void insert(HashTable hashTable, Value key, bool *errorCode) {
    if (hashTable == NULL || hashTable->size == hashTable->elementsAmount) {
        *errorCode = true;
        return;
    }
    const int hash = hashFunction(hashTable, key);
    for (int i = hash; ; i == hashTable->size ? i = 0 : ++i) {
        if (hashTable->table[i] == NULL) {
            hashTable->table[i] = key;
            return;
        }
    }
}

bool search(HashTable hashTable, Value key, bool *errorCode) {
    if (hashTable == NULL || key == NULL) {
        *errorCode = true;
        return false;
    }
    const int hash = hashFunction(hashTable, key);
    for (int i = hash; i < hashTable->size; ++i) {
        if (strcmp(hashTable->table[i], key) == 0) {
            return true;
        }
    }
    return false;
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