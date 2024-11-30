#pragma once
#include "list.h"

int hashFunction(int hashTableSize, Key key);

List ** createHashTable(int hashTableSize, bool * errorCode);

void updateHashTableByKey(List * hashTable[], int hashTableSize, Key key, bool * errorCode);