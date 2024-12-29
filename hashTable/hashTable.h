#pragma once

typedef char *Key;

typedef int Value;

typedef struct HashTable HashTable;

//creates table initialized with NULLs
HashTable *createHashTable(int hashTableSize, int *errorCode);

//if there is element with such key in the table increases frequency.
//else adds element making frequency = 1.
//uses updateListByKey.
void updateHashTable(HashTable *hashTable, Key key, int *errorCode);

//counts fill factor. if it < 2 nothing happens.
//else creates new table with bigger size and fills it with old values.
//the old table will be freed, reassign the pointer.
//changes hashTableSize to size of new hash table (that's why it's int * instead of const int)
void expandHashTable(HashTable **hashTable, int *errorCode);

//counts not amount of words in text, but amount of unique words
int countElementsAmount(HashTable *hashTable, int *errorCode);

int calculateMaxListLength(HashTable *hashTable, int hashTableSize, int *errorCode);

double calculateAverageListLength(HashTable *hashTable, int hashTableSize, int *errorCode);

double calculateFillFactor(HashTable *hashTable, int *errorCode);

//if word not in the table returns 0.
//else returns it's frequency in the text.
int findFrequencyByKey(HashTable *hashTable, int hashTableSize, Key key, int *errorCode);

//prints all words and it's frequencies in unordered form.
void printFrequencies(HashTable *hashTable, int *errorCode);

void deleteHashTable(HashTable **hashTable, int *errorCode);