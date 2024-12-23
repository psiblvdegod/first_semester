#include "list.h"
#include "hashTable.h"
#include "tests.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NO_ERRORS 0
#define MEMORY_ALLOCATION_ERROR 44
#define INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION 1
#define FILE_OPENING_ERROR 15
#define TESTS_FAILED_ERROR (-1)

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

int main(void) {
    int errorCode = 0;
    if (!hashTableTests() || !listTests()) {
        return -1;
    }

}