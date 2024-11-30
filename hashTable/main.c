#include "list.h"
#include "hashTable.h"
#include <stdio.h>
#include <stdlib.h>

void fillHashTable(List ** hashTable, const int hashTableSize, const char * path, bool * errorCode) {
    FILE * file = fopen(path, "r");
    if (file == NULL) {
        *errorCode = true;
        printf("File not found.\n");
        return;
    }
    bool inputValidation = true;
    while (inputValidation) {
        char * buffer = calloc(50, sizeof(char));
        if (buffer == NULL) {
            *errorCode = true;
            printf("Memory allocation error.\n");
            return;
        }
        inputValidation = fscanf(file, "%s", buffer) == 1;
        updateHashTableByKey(hashTable, hashTableSize, buffer, errorCode);
        if (*errorCode) {
            printf("Something went wrong.\n");
        }
    }
}

void printFrequencies(List ** hashTable, const int hashTableSize, bool * errorCode) {
    if (hashTable == NULL) {
        *errorCode = true;
        return;
    }
    for (int i = 0; i < hashTableSize; ++i) {
        if (hashTable[i] == NULL) continue;
        printf("%d %s\n", getFrequency(hashTable[i], errorCode), getKey(hashTable[i], errorCode));
    }
}

int main(void) {
    bool errorCode = false;
    const char * path = "/Users/psiblvdegod/Desktop/homework/hashTable/text.txt";
    const int hashTableSize = 100;
    List ** hashTable = createHashTable(hashTableSize, &errorCode);
    fillHashTable(hashTable, hashTableSize, path, &errorCode);
    printFrequencies(hashTable, hashTableSize, &errorCode);
}