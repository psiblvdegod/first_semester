#include "hashTable.h"
#include "errorCode.h"
#include "tests.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void fillHashTable(HashTable *hashTable, const char *path, int *errorCode) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        *errorCode = FILE_OPENING_ERROR;
        return;
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
            return;
        }
        free(buffer);
    }
    fclose(file);
}

int main(void) {
    int errorCode = NO_ERRORS;
    return hashTableTests();
}