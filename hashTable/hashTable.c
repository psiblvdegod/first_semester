#include "errorCode.h"
#include "hashTable.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
    Value frequency;
    Key key;
    struct Node *next;
} Node;

Node *createNode(Key key, int *errorCode) {
    Node *newNode = calloc(1, sizeof(Node));
    if (newNode == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }
    Key copy = calloc(WORD_SIZE, sizeof(char));
    if (copy == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        free(newNode);
        return NULL;
    }
    newNode->key = strcpy(copy, key);
    newNode->frequency = 1;
    return newNode;
}

Node *addNode(Node *node, Node *newNode, int *errorCode) {
    if (newNode == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return node;
    }
    if (node == NULL) {
        return newNode;
    }
    newNode->next = node;
    return newNode;
}

Node *findNode(Node *node, Key key, int *errorCode) {
    while (node != NULL) {
        if (node->key != NULL) {
            if (strcmp(node->key, key) == 0) {
                return node;
            }
        }
        else {
            *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
            return NULL;
        }
        node = node->next;
    }
    return node;
}

struct HashTable {
    Node **table;
    size_t size;
    size_t elementsAmount;
};

size_t hashFunction(const size_t hashTableSize, Key key) {
    if (hashTableSize < 1 || key == NULL) {
        return 0;
    }
    size_t result = 1;
    for (size_t i = 0; key[i] != '\0'; ++i) {
        result = (result + ((unsigned char) key[i]) * (i + 1)) % hashTableSize;
    }
    return result;
}

HashTable *createHashTable(const size_t size, int *errorCode) {
    if (size < 1) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return NULL;
    }
    HashTable *hashTable = calloc(1, sizeof(HashTable));
    if (hashTable == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }
    hashTable->size = size;
    hashTable->table = calloc(size, sizeof(Node));
    if (hashTable->table == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        free(hashTable);
    }
    return hashTable;
}

void expandHashTable(HashTable **hashTable, int *errorCode) {
    if (hashTable == NULL || *hashTable == NULL || (*hashTable)->table == NULL || (*hashTable)->size < 1) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    const double fillFactor = calculateFillFactor(*hashTable, errorCode);
    if (fillFactor < 2 || *errorCode != NO_ERRORS) {
        return;
    }
    const size_t newSize = (size_t)(fillFactor * ((double)(*hashTable)->size) * 2);
    HashTable *newHashTable = createHashTable(newSize, errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    for (size_t i = 0; i < (*hashTable)->size; ++i) {
        Node *cell = (*hashTable)->table[i];
        while (cell != NULL) {
            const size_t hash = hashFunction(newSize, cell->key);
            Node *newNode = createNode(cell->key, errorCode);
            if (*errorCode != NO_ERRORS) {
                deleteHashTable(&newHashTable, errorCode);
                return;
            }
            newNode->frequency = cell->frequency;
            newHashTable->table[hash] = addNode(newHashTable->table[hash], newNode, errorCode);
            if (*errorCode != NO_ERRORS) {
                deleteHashTable(&newHashTable, errorCode);
                return;
            }
            cell = cell->next;
        }
    }
    deleteHashTable(hashTable, errorCode);
    *hashTable = newHashTable;
}

void addWordToHashTable(HashTable **hashTable, Key key, int *errorCode) {
    if (hashTable == NULL || *hashTable == NULL || (*hashTable)->table == NULL || (*hashTable)->size < 1) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    const size_t hash = hashFunction((*hashTable)->size, key);
    Node *node = findNode((*hashTable)->table[hash], key, errorCode);
    if (node == NULL) {
        node = createNode(key, errorCode);
        if (*errorCode != NO_ERRORS) {
            free(node);
            return;
        }
        (*hashTable)->table[hash] = addNode((*hashTable)->table[hash], node, errorCode);
        ++(*hashTable)->elementsAmount;
        if (calculateFillFactor(*hashTable, errorCode) > 2) {
            expandHashTable(hashTable, errorCode);
        }
    }
    else {
        ++node->frequency;
    }
}

size_t calculateMaxListLength(HashTable *hashTable, int *errorCode) {
    if (hashTable == NULL || hashTable->table == NULL || hashTable->size < 1) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return -1;
    }
    size_t result = 0;
    for (size_t i = 0; i < hashTable->size; ++i) {
        Node *cell = hashTable->table[i];
        size_t listLength = 0;
        while (cell != NULL) {
            ++listLength;
            cell = cell->next;
        }
        result = result < listLength ? listLength : result;
    }
    return result;
}

double calculateAverageListLength(HashTable *hashTable, int *errorCode) {
    if (hashTable == NULL || hashTable->table == NULL || hashTable->size < 1) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return -1;
    }
    size_t amountOfNotEmptyCells = 0;
    for (size_t i = 0; i < hashTable->size; ++i) {
        if (hashTable->table[i] != NULL) {
            ++amountOfNotEmptyCells;
        }
    }
    return ((double) hashTable->elementsAmount) / ((double) amountOfNotEmptyCells);
}


unsigned int findFrequency(HashTable *hashTable, Key key, int *errorCode) {
    if (hashTable == NULL || hashTable->table == NULL || hashTable->size < 1) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return -1;
    }
    const size_t hash = hashFunction(hashTable->size, key);
    Node *cell = hashTable->table[hash];
    while (cell != NULL) {
        if (cell->key == NULL) {
            *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
            return 0;
        }
        if (strcmp(key, cell->key) == 0) {
            return cell->frequency;
        }
        cell = cell->next;
    }
    return 0;
}

double calculateFillFactor(HashTable *hashTable, int *errorCode) {
    if (hashTable == NULL || hashTable->table == NULL || hashTable->size < 1) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return -1;
    }
    return (double)(hashTable->elementsAmount) / (double)(hashTable->size);
}

void printFrequencies(HashTable *hashTable, int *errorCode) {
    if (hashTable == NULL || hashTable->table == NULL || hashTable->size < 1) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    for (size_t i = 0; i < hashTable->size; ++i) {
        Node *cell = hashTable->table[i];
        while (cell != NULL) {
            printf("%s - %d\n", cell->key, cell->frequency);
            cell = cell->next;
        }
    }
}

void deleteList(Node *node) {
    while (node != NULL) {
        Node *temp = node;
        node = node->next;
        free(temp->key);
        free(temp);
    }
}

void deleteHashTable(HashTable **hashTable, int *errorCode) {
    if (hashTable == NULL || *hashTable == NULL || (*hashTable)->table == NULL || (*hashTable)->size < 1) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    for (size_t i = 0; i < (*hashTable)->size; ++i) {
        deleteList((*hashTable)->table[i]);
    }
    free(*hashTable);
    *hashTable = NULL;
}