#pragma once
#include "tree.h"

typedef struct Dictionary Dictionary;

Value searchInDictionary(Dictionary *dictionary, Key key, int *errorCode);

bool addToDictionary(Dictionary *dictionary, Value value, Key key, int *errorCode);

bool deleteFromDictionary(Dictionary *dictionary, Key key, int *errorCode);