#pragma once
#include "list.h"

typedef List* HashTable;

//if input is not correct returns 0
//else returns the number obtained by some algorithm.
//it is not injective mapping to the range from 0 to hashTableSize - 1
int hashFunction(int hashTableSize, Key key);

//creates table initialized with NULLs
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

//counts not amount of words in text, but amount of unique words
int countElementsAmount(HashTable hashTable, int hashTableSize, bool * errorCode);

int calculateMaxListLength(HashTable hashTable, int hashTableSize, bool * errorCode);

double calculateAverageListLength(HashTable hashTable, int hashTableSize, bool * errorCode);

double calculateFillFactor(HashTable hashTable, int hashTableSize, bool * errorCode);

//if word not in the table returns 0.
//else returns it's frequency in the text.
int findFrequencyByKey(HashTable hashTable, int hashTableSize, Key key, bool * errorCode);

//prints all words and it's frequencies in unordered form.
void printFrequencies(HashTable hashTable, int hashTableSize, bool * errorCode);