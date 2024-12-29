#include "fileProcessing.h"
#include "errorCode.h"
#include <stdio.h>

HashTable *getFrequenciesFromFile(const int hashTableSize, const char *filePath, int *errorCode) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        *errorCode = FILE_OPENING_ERROR;
        return NULL;
    }
    HashTable *hashTable = createHashTable(hashTableSize, errorCode);
    if (*errorCode != NO_ERRORS) {
        fclose(file);
        return NULL;
    }
    while (!feof(file)) {
        char buffer[50] = {'0'};
        fscanf(file, "%s", buffer);
        updateHashTable(hashTable, buffer, errorCode);
        if (*errorCode) {
            break;
        }
    }
    if (*errorCode != NO_ERRORS) {
    }
    fclose(file);
    return hashTable;
}