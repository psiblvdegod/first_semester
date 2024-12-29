#include "hashTable.h"
#include "errorCode.h"
#include "tests.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

HashTable *getFrequenciesFromFile(const char *path, int *errorCode) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        *errorCode = FILE_OPENING_ERROR;
        return NULL;
    }
    HashTable *hashTable = createHashTable(100, errorCode);
    if (*errorCode != NO_ERRORS) {
        fclose(file);
        return NULL;
    }
    while (!feof(file)) {
        char *buffer = calloc(50, sizeof(char));
        if (buffer == NULL) {
            *errorCode = MEMORY_ALLOCATION_ERROR;
            break;
        }
        fscanf(file, "%s", buffer);
        updateHashTable(hashTable, buffer, errorCode);
        if (*errorCode) {
            break;
        }
        free(buffer);
    }
    if (*errorCode != NO_ERRORS) {
    }
    fclose(file);
    return hashTable;
}

int main(void) {
    int errorCode = NO_ERRORS;
    HashTable *hashTable = getFrequenciesFromFile("../text.txt", &errorCode);
    //printFrequencies(hashTable, &errorCode);
    expandHashTable(&hashTable, &errorCode);
    printFrequencies(hashTable, &errorCode);
    deleteHashTable(&hashTable, &errorCode);
    return errorCode;
}