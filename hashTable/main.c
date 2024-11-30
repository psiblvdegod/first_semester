#include "list.h"
#include "hashTable.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void fillHashTable(List ** hashTable, const int hashTableSize, const char * path, bool * errorCode) {
    FILE * file = fopen(path, "r");
    if (file == NULL) {
        *errorCode = true;
        printf("File not found.\n");
        return;
    }
    while (true) {
        char * buffer = calloc(50, sizeof(char));
        if (buffer == NULL) {
            *errorCode = true;
            printf("Memory allocation error.\n");
            return;
        }
        bool inputValidation = fscanf(file, "%s", buffer) == 1;
        if (!inputValidation) return;
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
        printf("%s - %d\n", getKey(hashTable[i], errorCode), getFrequency(hashTable[i], errorCode));
    }
}

int findFrequencyByKey(List ** hashTable, const int hashTableSize, Key key, bool * errorCode) {
    if (hashTable == NULL) {
        *errorCode = true;
        return -1;
    }
    int hash = hashFunction(hashTableSize, key);
    List * list = hashTable[hash];
    while (list != NULL) {
        if (strcmp(key, getKey(list, errorCode)) == 0) {
            return getFrequency(list, errorCode);
        }
        list = getPrevious(list);
    }
    return 0;
}

int main(void) {
    bool errorCode = false;
    const char * path = "/Users/psiblvdegod/Desktop/homework/hashTable/text.txt";
    const int hashTableSize = 100;
    List ** hashTable = createHashTable(hashTableSize, &errorCode);
    fillHashTable(hashTable, hashTableSize, path, &errorCode);
    if (errorCode) {
        printf("Something went wrong.\n");
        return -1;
    }
    printf("1 - get frequency by key. 2 - print all frequencies.\n");
    int userQuery = 0;
    int inputValidation = scanf("%d", &userQuery);
    if (inputValidation != 1) {
        printf("Invalid value.\n");
        return -1;
    }
    if (userQuery == 1) {
        printf("Enter key.\n");
        char * key = calloc(50, sizeof (char));
        if (key == NULL) {
            printf("Memory allocation error.\n");
            return -1;
        }
        inputValidation = scanf("%s", key);
        if (inputValidation != 1) {
            printf("Invalid value.\n");
            return -1;
        }
        const int frequency = findFrequencyByKey(hashTable, hashTableSize, key, &errorCode);
        if (errorCode) {
            printf("Something went wrong.\n");
            return -1;
        }
        printf("%s - %d\n", key, frequency);
    }
    else if (userQuery == 2) {
        printFrequencies(hashTable, hashTableSize, &errorCode);
    }
}