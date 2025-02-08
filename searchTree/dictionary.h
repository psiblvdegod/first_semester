#pragma once

#include "tree.h"

typedef struct Dictionary Dictionary;

// creates empty dictionary
Dictionary *createDictionary(int *errorCode);

// searches value in dictionary by key
Value searchInDictionary(Dictionary *dictionary, Key key, int *errorCode);

// adds key and value corresponding to it
bool addToDictionary(Dictionary *dictionary, Value value, Key key, int *errorCode);

// deletes key and value corresponding to it
bool deleteFromDictionary(Dictionary *dictionary, Key key, int *errorCode);

// frees allocated memory and turns pointer NULL
void deleteDictionary(Dictionary **dictionary, int *errorCode);