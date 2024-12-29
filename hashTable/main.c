#include "list.h"
#include "hashTable.h"
#include "errorCode.h"
#include "tests.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
void fillHashTable(HashTable hashTable, const int hashTableSize, const char *path, int *errorCode) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        *errorCode = FILE_OPENING_ERROR;
        return;
    }
    while (true) {
        char *buffer = calloc(50, sizeof(char));
        if (buffer == NULL) {
            *errorCode = MEMORY_ALLOCATION_ERROR;
            break;
        }
        if (fscanf(file, "%s", buffer) != 1) {
            break;
        }
        updateHashTable(hashTable, hashTableSize, buffer, errorCode);
        if (*errorCode) {
            return;
        }
    }
    fclose(file);
}
*/
int main(void) {
    int errorCode = NO_ERRORS;
    return test();
}