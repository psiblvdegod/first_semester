#include "hashTable.h"
#include <stdlib.h>

int hashFunction(const int hashTableSize, Key key) {
    int result = 1;
    for (int i = 0; key[i] != '\0'; ++i) {
        result = (result + (unsigned char) key[i]) % hashTableSize;
    }
    return result;
}

List ** createHashTable(const int hashTableSize, bool * errorCode) {
    List ** hashTable = calloc(hashTableSize, 24); //43X
    if (hashTable == NULL) {
        *errorCode = true;
        return NULL;
    }
    return hashTable;
}

void updateHashTableByKey(List ** hashTable, const int hashTableSize, Key key, bool * errorCode) {
    if (hashTable == NULL) {
        *errorCode = true;
        return;
    }
    const int hash = hashFunction(hashTableSize, key);
    hashTable[hash] = updateListByKey(hashTable[hash], key, errorCode);
}