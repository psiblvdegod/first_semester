#pragma once
#include "list.h"

typedef List* HashTable;

int hashFunction(int hashTableSize, Key key);

HashTable createHashTable(int hashTableSize, bool * errorCode);

//if there is element with such key in the table increases frequency.
//else adds element making frequency = 1.
//uses updateListByKey.
void updateHashTable(HashTable hashTable, int hashTableSize, Key key, bool * errorCode);

//counts fill factor. if it < 2 nothing happens.
//else creates new table with bigger size and fills it with old values.
//the old table will be freed, reassign the pointer.
//changes hashTableSize to size of new hash table (that's why it's int * instead of const int)
HashTable expandHashTable(HashTable hashTable, int * hashTableSize, bool * errorCode);

int countElementsAmount(HashTable hashTable, int hashTableSize, bool * errorCode);

int calculateMaxListLength(HashTable hashTable, int hashTableSize, bool * errorCode);

double calculateAverageListLength(HashTable hashTable, int hashTableSize, bool * errorCode);

double calculateFillFactor(HashTable hashTable, int hashTableSize, bool * errorCode);

int findFrequencyByKey(HashTable hashTable, int hashTableSize, Key key, bool * errorCode);

void printFrequencies(HashTable hashTable, int hashTableSize, bool * errorCode);