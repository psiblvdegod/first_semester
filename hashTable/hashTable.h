#pragma once
#include "list.h"

typedef List* HashTable;

int hashFunction(int hashTableSize, Key key);

HashTable createHashTable(int hashTableSize, bool * errorCode);

//if there is element with such key in the table increases frequency.
//else adds element making frequency = 1.
//uses updateListByKey.
void updateHashTableByKey(HashTable hashTable, int hashTableSize, Key key, bool * errorCode);

int countElementsAmount(HashTable hashTable, int hashTableSize, bool * errorCode);

int calculateMaxListLength(HashTable hashTable, int hashTableSize, bool * errorCode);

double calculateAverageListLength(HashTable hashTable, int hashTableSize, bool * errorCode);

double calculateFillFactor(HashTable hashTable, int hashTableSize, bool * errorCode);

int findFrequencyByKey(HashTable hashTable, int hashTableSize, Key key, bool * errorCode);