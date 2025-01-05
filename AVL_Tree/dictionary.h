#pragma once

#include "typeDefinitions.h"

typedef struct Dictionary Dictionary;

// creates empty dictionary
Dictionary *createDictionary(int *errorCode);

// adds element with required value and key to dictionary
void addToDictionary(Dictionary *dictionary, Value value, Key key, int *errorCode);

// if there is element with such key in dictionary returns it`s value
// else returns nullptr
Value searchInDictionary(Dictionary *dictionary, Key key, int *errorCode);

// deletes element from dictionary
void deleteFromDictionary(Dictionary *dictionary, Key key, int *errorCode);

// frees allocated memory and turns pointer NULL
void deleteDictionary(Dictionary **dictionary, int *errorCode);