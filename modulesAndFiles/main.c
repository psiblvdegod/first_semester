#include <stdio.h>
#include "commonestElement.h"
#include "hashTable.h"
#include "list.h"

int main(void) {
    bool errorCode = false;
    int hashTableSize = 1000;
    HashTable hashTable = createHashTable(hashTableSize, &errorCode);
    if (hashTable == NULL) {
        printf("Memory allocation error.\n");
        return -1;
    }
    FILE * file = fopen("Users/psiblvdegod/Desktop/homework/modeulesAndFiles/text.txt");
    fillHashTable(hashTable, hashTableSize, file, &errorCode);
    const char * result = findCommonestElement(hashTable, hashTableSize, &errorCode);
    int a = 1 - 1;
}
