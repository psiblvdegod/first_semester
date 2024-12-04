#include "list.h"
#include "hashTable.h"
#include "tests.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void fillHashTable(HashTable hashTable, const int hashTableSize, const char * path, bool * errorCode) {
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
            break;
        }
        if (fscanf(file, "%s", buffer) != 1) break;
        updateHashTableByKey(hashTable, hashTableSize, buffer, errorCode);
        if (*errorCode) {
            printf("Something went wrong.\n");
        }
    }
    fclose(file);
}

int main(void) {
    if (!hashTableTests() || !listTests()) {
        printf("Error. Tests failed.\n");
        return -1;
    }
    bool errorCode = false;
    const char * path = "/Users/psiblvdegod/Desktop/homework/hashTable/text.txt";
    const int hashTableSize = 100;
    HashTable hashTable = createHashTable(hashTableSize, &errorCode);
    fillHashTable(hashTable, hashTableSize, path, &errorCode);
    hashTable = expandHashTable(hashTable, hashTableSize, &errorCode);
    if (errorCode) {
        printf("Something went wrong.\n");
        return -1;
    }
    printf("1 - get frequency by key. 2 - print all frequencies. 3 - print fill factor, max and average list length\n");
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
    else if (userQuery == 3) {
        const double fillFactor = calculateFillFactor(hashTable, hashTableSize, &errorCode);
        const double averageListLength = calculateAverageListLength(hashTable, hashTableSize, &errorCode);
        const int maxListLength = calculateMaxListLength(hashTable, hashTableSize, &errorCode);
        if (errorCode) {
            printf("Something went wrong.\n");
            return -1;
        }
        printf("fill factor: %lf\n", fillFactor);
        printf("average list length: %lf\n", averageListLength);
        printf("max list length: %d\n", maxListLength);
    }
}