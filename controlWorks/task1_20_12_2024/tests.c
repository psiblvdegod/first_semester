#include "tests.h"
#include "hashTable.h"

bool hashTableTests() {
    bool errorCode = false;
    HashTable hashTable = createHashTable(5, &errorCode);
    if (errorCode) {
        return false;
    }
    const char *string1 = "string";
    const char *string2 = "";
    insert(hashTable, string1, &errorCode);
    insert(hashTable, string2, &errorCode);
    const bool test1 = search(hashTable, "string", &errorCode);
    const bool test2 = search(hashTable, "", &errorCode);
    const bool test3 = !search(hashTable, " ", &errorCode);
    return test1 && test2 && test3 && !errorCode;
}