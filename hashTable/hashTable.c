#include "errorCode.h"
#include "hashTable.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
    Value frequency;
    Key key;
    struct Node *next;
} Node;

struct HashTable {
    Node **table;
    int size;
};

unsigned int hashFunction(const int hashTableSize, Key key) {
    if (hashTableSize < 1 || key == NULL) {
        return 0;
    }
    unsigned int result = 1;
    for (int i = 0; key[i] != '\0'; ++i) {
        result = (result + ((unsigned char) key[i]) * i) % hashTableSize;
    }
    return result;
}

HashTable *createHashTable(const int size, int *errorCode) {
    if (size <= 0) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return NULL;
    }
    HashTable *hashTable = calloc(1, sizeof(HashTable));
    if (hashTable == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }
    hashTable->table = calloc(size, sizeof(Node));
    if (hashTable->table == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        free(hashTable);
    }
    return hashTable;
}

Node *createNode(Key key, int *errorCode) {
    Node *newNode = calloc(1, sizeof(Node));
    if (newNode == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }
    newNode->key = key;
    return newNode;
}

Node *addNode(Node *node, Node *newNode, int *errorCode) {
    if (node == NULL) {
        return newNode;
    }
    node->next = newNode;
    return newNode;
}

Node *search(Node *node, Key key) {
    while (node != NULL && node->key != key) {
        node = node->next;
    }
    return node;
}

void updateHashTable(HashTable *hashTable, Key key, int *errorCode) {
    if (hashTable == NULL || hashTable->table == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    const unsigned int hash = hashFunction(hashTable->size, key);
    Node *node = search(hashTable->table[hash], key);
    if (node == NULL) {
        node = createNode(key, errorCode);
    }
    hashTable->table[hash] = addNode(hashTable->table[hash], node, errorCode);
}
/*
int countElementsAmount(HashTable *hashTable, int *errorCode) {
    if (hashTable == NULL || hashTable->table == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return -1;
    }
    int result = 0;
    for (int i = 0; i < hashTable->size; ++i) {
        List tableElement = hashTable->table[i];
        while (tableElement != NULL) {
            ++result;
            tableElement = getPrevious(tableElement);
        }
    }
    return result;
}

int calculateMaxListLength(HashTable *hashTable, int *errorCode) {
    if (hashTable == NULL || hashTable->table == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return -1;
    }
    int result = 0;
    for (int i = 0; i < hashTable->size; ++i) {
        List tableElement = hashTable->table[i];
        int tableElementLength = 0;
        while (tableElement != NULL) {
            ++tableElementLength;
            tableElement = getPrevious(tableElement);
        }
        result = result > tableElementLength ? result : tableElementLength;
    }
    return result;
}

double calculateAverageListLength(HashTable *hashTable, int *errorCode) {
    if (hashTable == NULL || hashTable->table == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return -1;
    }
    int amountOfNotEmptyCells = 0;
    const int elementsAmount = countElementsAmount(hashTable, errorCode);
    for (int i = 0; i < hashTable->size; ++i) {
        if (hashTable->table[i] != NULL) {
            ++amountOfNotEmptyCells;
        }
    }
    return ((double) elementsAmount) / ((double) amountOfNotEmptyCells);
}

double calculateFillFactor(HashTable *hashTable, int *errorCode) {
    if (hashTable == NULL || hashTable->table == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return -1;
    }
    const int elementsAmount = countElementsAmount(hashTable, errorCode);
    return ((double) elementsAmount) / ((double) hashTable->size);
}

int findFrequencyByKey(HashTable *hashTable, Key key, int *errorCode) {
    if (hashTable == NULL || hashTable->table == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return -1;
    }
    const int hash = hashFunction(hashTable->size, key);
    List list = hashTable->table[hash];
    while (list != NULL) {
        if (strcmp(key, getKey(list, errorCode)) == 0) {
            return getFrequency(list, errorCode);
        }
        list = getPrevious(list);
    }
    return 0;
}

HashTable *expandHashTable(HashTable *hashTable, int *errorCode) {
    if (hashTable == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return hashTable;
    }
    const double fillFactor = calculateFillFactor(hashTable, errorCode);
    if (fillFactor < 2) {
        return hashTable;
    }
    const int newSize = (int)(fillFactor * (hashTable->size) * 2);
    HashTable *newHashTable = createHashTable(newSize, errorCode);
    if (*errorCode != NO_ERRORS) {
        return hashTable;
    }
    for (int i = 0; i < hashTable->size; ++i) {
        while (hashTable->table[i] != NULL) {
            Key key = hashTable->table[i];
            const int hash = hashFunction(newSize, getKey(hashTable->table[i], errorCode));
            newHashTable[hash] = updateList(newHashTable[hash], , getFrequency(hashTable[i], errorCode), errorCode);
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

void deleteHashTable(HashTable *hashTable, int *errorCode) {
    if (hashTable == 0 || hashTable->) {
        *errorCode =
    }
}
 */