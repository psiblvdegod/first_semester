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
        result = (result + ((unsigned char) key[i]) * (i + 1)) % hashTableSize;
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
    hashTable->size = size;
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

Node *addNode(Node *list, Node *newNode, int *errorCode) {
    if (newNode == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return list;
    }
    if (list == NULL) {
        return newNode;
    }
    newNode->next = list;
    return newNode;
}

Node *search(Node *list, Key key) {
    while (list != NULL && strcmp(list->key, key) != 0) {
        list = list->next;
    }
    return list;
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
        if (*errorCode != NO_ERRORS) {
            free(node);
            return;
        }
        hashTable->table[hash] = addNode(hashTable->table[hash], node, errorCode);
    }
    else {
        ++node->frequency;
    }
}


int calculateMaxListLength(HashTable *hashTable, int *errorCode) {
    if (hashTable == NULL || hashTable->table == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return -1;
    }
    int result = 0;
    for (int i = 0; i < hashTable->size; ++i) {
        Node *cell = hashTable->table[i];
        int listLength = 0;
        while (cell != NULL) {
            ++listLength;
            cell = cell->next;
        }
        result = result < listLength ? listLength : result;
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


int findFrequency(HashTable *hashTable, Key key, int *errorCode) {
    if (hashTable == NULL || hashTable->table == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return -1;
    }
    const unsigned int hash = hashFunction(hashTable->size, key);
    Node *cell = hashTable->table[hash];
    while (cell != NULL) {
        if (strcmp(key, cell->key) == 0) {
            return cell->frequency;
        }
        cell = cell->next;
    }
    return 0;
}

int countElementsAmount(HashTable *hashTable, int *errorCode) {
    if (hashTable == NULL || hashTable->table == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return -1;
    }
    int result = 0;
    for (int i = 0; i < hashTable->size; ++i) {
        Node *cell = hashTable->table[i];
        while (cell != NULL) {
            ++result;
            cell = cell->next;
        }
    }
    return result;
}


double calculateFillFactor(HashTable *hashTable, int *errorCode) {
    if (hashTable == NULL || hashTable->table == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return -1;
    }
    const int elementsAmount = countElementsAmount(hashTable, errorCode);
    return ((double) elementsAmount) / ((double) hashTable->size);
}


void expandHashTable(HashTable **hashTable, int *errorCode) {
    if (hashTable == NULL || *hashTable == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    const double fillFactor = calculateFillFactor(*hashTable, errorCode);
    if (fillFactor < 2) {
        return;
    }
    const int newSize = (int)(fillFactor * ((*hashTable)->size) * 2);
    HashTable *newHashTable = createHashTable(newSize, errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    for (int i = 0; i < (*hashTable)->size; ++i) {
        Node *cell = (*hashTable)->table[i];
        while (cell != NULL) {
            const unsigned int hash = hashFunction(newSize, cell->key);
            Node *newNode = createNode(cell->key, errorCode);
            if (*errorCode != NO_ERRORS) {
                //
                return;
            }
            newNode->frequency = cell->frequency;
            newHashTable->table[hash] = addNode(newHashTable->table[hash], newNode, errorCode);
            cell = cell->next;
        }
    }
    deleteHashTable(hashTable, errorCode);
    *hashTable = newHashTable;
}

void printFrequencies(HashTable *hashTable, int *errorCode) {
    if (hashTable == NULL || hashTable->table == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    for (int i = 0; i < hashTable->size; ++i) {
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
    if (hashTable == NULL || *hashTable == NULL || (*hashTable)->table == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    for (int i = 0; i < (*hashTable)->size; ++i) {
        deleteList((*hashTable)->table[i]);
    }
    free(*hashTable);
    *hashTable = NULL;
}