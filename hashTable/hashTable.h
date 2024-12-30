#pragma once
#include <stdlib.h>

#define WORD_SIZE 50

typedef char *Key;

typedef unsigned int Value;

typedef struct HashTable HashTable;

// creates empty hash table with of required size,
// hashtable will expand as elements are added.
HashTable *createHashTable(size_t hashTableSize, int *errorCode);

// if there is element with such key in the table,
// increases frequency by one.
// else adds it to table.
void addWordToHashTable(HashTable **hashTable, Key key, int *errorCode);

// returns the maximum of lists' lengths.
size_t findMaxListLength(HashTable *hashTable, int *errorCode);

// returns average length of not-empty lists.
double calculateAverageListLength(HashTable *hashTable, int *errorCode);

// calculates fill factor of hash table.
double calculateFillFactor(HashTable *hashTable, int *errorCode);

// if word not in the table returns 0.
// else returns it's frequency in the text.
unsigned int findFrequency(HashTable *hashTable, Key key, int *errorCode);

// frees allocated memory and turns pointer NULL.
void deleteHashTable(HashTable **hashTable, int *errorCode);