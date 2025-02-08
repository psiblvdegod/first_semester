#include "fileProcessing.h"
#include "errorCode.h"
#include <stdio.h>

HashTable *getFrequenciesFromFile(const char *filePath, int *errorCode) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        *errorCode = FILE_OPENING_ERROR;
        return NULL;
    }
    HashTable *hashTable = createHashTable(errorCode);
    if (*errorCode != NO_ERRORS) {
        fclose(file);
        return NULL;
    }
    while (!feof(file)) {
        char buffer[WORD_MAX_SIZE] = {'0'};
        fscanf(file, "%s", buffer);
        addWordToHashTable(&hashTable, buffer, errorCode);
        if (*errorCode != NO_ERRORS) {
            break;
        }
    }
    if (*errorCode != NO_ERRORS) {
        deleteHashTable(&hashTable, errorCode);
    }
    fclose(file);
    return hashTable;
}