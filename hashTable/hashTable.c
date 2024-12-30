#include "errorCode.h"
#include "hashTable.h"
#include <string.h>
#include <stdlib.h>

typedef struct List {
    Value frequency;
    Key key;
    struct List *next;
} List;

List *createElement(Key key, int *errorCode) {
    List *newElement = calloc(1, sizeof(List));
    if (newElement == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }
    Key keyCopy = calloc(WORD_SIZE, sizeof(char));
    if (keyCopy == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        free(newElement);
        return NULL;
    }
    newElement->key = strcpy(keyCopy, key);
    newElement->frequency = 1;
    return newElement;
}

List *addElement(List *list, List *newElement, int *errorCode) {
    if (newElement == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return list;
    }
    newElement->next = list;
    return newElement;
}

List *findElement(List *list, Key key, int *errorCode) {
    while (list != NULL) {
        if (list->key != NULL) {
            if (strcmp(list->key, key) == 0) {
                return list;
            }
        }
        else {
            *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
            return NULL;
        }
        list = list->next;
    }
    return NULL;
}

void deleteList(List *list) {
    while (list != NULL) {
        List *temp = list;
        list = list->next;
        free(temp->key);
        free(temp);
    }
}

struct HashTable {
    List **table;
    size_t size;
    size_t elementsAmount;
};

size_t hashFunction(const size_t hashTableSize, Key key, int *errorCode) {
    if (hashTableSize < 1 || key == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
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
    hashTable->table = calloc(size, sizeof(List));
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
    const size_t newSize = (size_t)(fillFactor * (double)(*hashTable)->size * 2);
    HashTable *newHashTable = createHashTable(newSize, errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    for (size_t i = 0; i < (*hashTable)->size; ++i) {
        List *cell = (*hashTable)->table[i];
        while (cell != NULL) {
            const size_t hash = hashFunction(newSize, cell->key, errorCode);
            List *newElement = createElement(cell->key, errorCode);
            if (*errorCode != NO_ERRORS) {
                deleteHashTable(&newHashTable, errorCode);
                return;
            }
            newElement->frequency = cell->frequency;
            newHashTable->table[hash] = addElement(newHashTable->table[hash], newElement, errorCode);
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
    const size_t hash = hashFunction((*hashTable)->size, key, errorCode);
    List *list = findElement((*hashTable)->table[hash], key, errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    if (list == NULL) {
        list = createElement(key, errorCode);
        if (*errorCode != NO_ERRORS) {
            return;
        }
        (*hashTable)->table[hash] = addElement((*hashTable)->table[hash], list, errorCode);
        if (*errorCode != NO_ERRORS) {
            deleteList((*hashTable)->table[hash]);
            return;
        }
        ++(*hashTable)->elementsAmount;
        if (calculateFillFactor(*hashTable, errorCode) > 2) {
            expandHashTable(hashTable, errorCode);
        }
    }
    else {
        ++list->frequency;
    }
}

size_t findMaxListLength(HashTable *hashTable, int *errorCode) {
    if (hashTable == NULL || hashTable->table == NULL || hashTable->size < 1) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return -1;
    }
    size_t result = 0;
    for (size_t i = 0; i < hashTable->size; ++i) {
        List *cell = hashTable->table[i];
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
    if (hashTable == NULL || hashTable->table == NULL || hashTable->size < 1 || key == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return -1;
    }
    const size_t hash = hashFunction(hashTable->size, key, errorCode);
    List *cell = hashTable->table[hash];
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

