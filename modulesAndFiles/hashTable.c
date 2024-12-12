#include "hashTable.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct HashTableInternals {
    List * table;
    int size;
} HashTableInternals;

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
    List * table = calloc(hashTableSize, sizeof(List));
    if (table == NULL) {
        *errorCode = true;
        return NULL;
    }
    HashTable hashTable = calloc(1, sizeof(HashTableInternals));
    hashTable->table = table;
    hashTable->size = hashTableSize;
    return hashTable;
}

void fillHashTable(HashTable hashTable, FILE * file, bool * errorCode) {
    if (file == NULL) {
        *errorCode = true;
        printf("File not found.\n");
        return;
    }
    while (true) {
        char * buffer = calloc(50, sizeof(char));
        if (buffer == NULL) {
            *errorCode = true;
            printf("Memory allocation error.\n");
            break;
        }
        if (fscanf(file, "%s", buffer) != 1) {
            break;
        }
        updateHashTable(hashTable, buffer, errorCode);
        if (*errorCode) {
            printf("Something went wrong.\n");
            return;
        }
    }
}

void updateHashTable(HashTable hashTable, Key key, bool *errorCode) {
    if (hashTable == NULL || hashTable->size <= 0) {
        *errorCode = true;
        return;
    }
    const int hash = hashFunction(hashTable->size, key);
    hashTable->table[hash] = updateList(hashTable->table[hash], key, 1, errorCode);
}

const char *findCommonestElement(HashTable hashTable, bool * errorCode) {
    if (hashTable == NULL) {
        *errorCode = true;
        return NULL;
    }
    char * result = NULL;
    int currentMaxAmount = 0;
    for (int i = 0; i < hashTable->size; ++i) {
        List tableElement = hashTable->table[i];
        while (tableElement != NULL) {
            const int frequency = getFrequency(tableElement, errorCode);
            const char * key = getKey(tableElement, errorCode);
            if (currentMaxAmount < frequency) {
                currentMaxAmount = frequency;
                result = (char *)key;
            }
            tableElement = getPrevious(tableElement);
        }
    }
    return result;
}
