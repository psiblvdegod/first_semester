#pragma once
#include <stdbool.h>

typedef const char* Value;

typedef struct HashTable *HashTable;

//creates table initialized with NULLs
HashTable createHashTable(int hashTableSize, bool * errorCode);

void insert(HashTable hashTable, Value key, bool *errorCode);

bool search(HashTable hashTable, Value key, bool *errorCode);