#include "hashTable.h"
#include <string.h>
#include <stdlib.h>

struct HashTable {
    Value *table;
    int size;
    int elementsAmount;
};

HashTable createHashTable(const int size, bool *errorCode) {
    if (size < 1) {
        *errorCode = true;
        return NULL;
    }
    HashTable hashTable = calloc(1, sizeof(struct HashTable));
    if (hashTable == NULL) {
        *errorCode = true;
        return NULL;
    }
    hashTable->table = calloc(size, sizeof(Value));
    if (hashTable->table == NULL) {
        *errorCode = true;
        return NULL;
    }
    hashTable->size = size;
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
    if (hashTable == NULL || key == NULL ||hashTable->size == hashTable->elementsAmount) {
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
        if (hashTable->table[i] == NULL) {
            continue;
        }
        if (strcmp(hashTable->table[i], key) == 0) {
            return true;
        }
    }
    return false;
}