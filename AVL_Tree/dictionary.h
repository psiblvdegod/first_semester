#pragma once

typedef struct Dictionary Dictionary;

Dictionary *createDictionary(int *errorCode);

void addToDictionary(Dictionary *dictionary, Value value, Key key, int *errorCode);

Value searchInDictionary(Dictionary *dictionary, Key key, int *errorCode);

void deleteFromDictionary(Dictionary *dictionary, Key key, int *errorCode);

void deleteDictionary(Dictionary **dictionary, int *errorCode);