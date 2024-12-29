#pragma once
#include "hashTable.h"

// creates hash table and fills it with frequencies from file
HashTable *getFrequenciesFromFile(size_t hashTableSize, const char *filePath, int *errorCode);