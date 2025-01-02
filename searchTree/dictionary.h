#pragma once

#include "tree.h"

typedef struct Dictionary Dictionary;

Dictionary *createDictionary(int *errorCode);

Value searchInDictionary(Dictionary *dictionary, Key key, int *errorCode);

bool addToDictionary(Dictionary *dictionary, Value value, Key key, int *errorCode);

bool deleteFromDictionary(Dictionary *dictionary, Key key, int *errorCode);

void deleteDictionary(Dictionary **dictionary, int *errorCode);