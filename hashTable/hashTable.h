#pragma once
#include <stdlib.h>

#define WORD_SIZE 50

typedef char *Key;

typedef unsigned int Value;

typedef struct HashTable HashTable;

// creates empty hash table with of required size
HashTable *createHashTable(size_t hashTableSize, int *errorCode);

// if there is element with such key in the table,
// increases frequency by one.
// else adds it to table.
void addWordToHashTable(HashTable **hashTable, Key key, int *errorCode);

size_t calculateMaxListLength(HashTable *hashTable, int *errorCode);

double calculateAverageListLength(HashTable *hashTable, int *errorCode);

double calculateFillFactor(HashTable *hashTable, int *errorCode);

//if word not in the table returns 0.
//else returns it's frequency in the text.
unsigned int findFrequency(HashTable *hashTable, Key key, int *errorCode);

//prints all words and it's frequencies in unordered form.
void printFrequencies(HashTable *hashTable, int *errorCode);

void deleteHashTable(HashTable **hashTable, int *errorCode);