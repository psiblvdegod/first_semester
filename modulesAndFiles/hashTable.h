#pragma once
#include "list.h"
#include <stdio.h>

typedef struct HashTableInternals *HashTable;

//if input is not correct returns 0
//else returns the number obtained by some algorithm.
//it is not injective mapping to the range from 0 to hashTableSize - 1
int hashFunction(int hashTableSize, Key key);

//creates table initialized with NULLs
HashTable createHashTable(int hashTableSize, bool * errorCode);

//if there is element with such key in the table increases frequency.
//else adds element making frequency = 1.
//uses updateListByKey.
void updateHashTable(HashTable hashTable, Key key, bool * errorCode);

//opens file for read and fills hashTable with frequencies of text
void fillHashTable(HashTable hashTable, FILE * file, bool * errorCode);

//finds the commonest sequence of characters separated by spaces in the text
const char *findCommonestElement(HashTable hashTable, bool * errorCode);