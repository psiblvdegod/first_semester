#pragma once
#include <stdbool.h>

typedef const char* Value;

typedef struct HashTable *HashTable;

// creates hashTable.
// reports an error if memory allocation is failed or size < 1.
HashTable createHashTable(int size, bool *errorCode);

// adds element to hashTable.
// report an error if arguments are incorrect or hash table is overflowed.
void insert(HashTable hashTable, Value key, bool *errorCode);

// return true if there is such element in the table,
// else returns false.
// report an error if arguments are incorrect.
bool search(HashTable hashTable, Value key, bool *errorCode);