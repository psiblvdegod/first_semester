#pragma once
#include "hashTable.h"

// creates hash table and fills it with frequencies from file
HashTable *getFrequenciesFromFile(int hashTableSize, const char *filePath, int *errorCode);