#pragma once

typedef struct Dictionary Dictionary;

Dictionary *createDictionary(int *errorCode);

void addToDictionary(Dictionary *dictionary, Value value, Value key, int *errorCode);

Value searchInDictionary(Dictionary *dictionary, Value key, int *errorCode);

void deleteFromDictionary(Dictionary *dictionary, Value key, int *errorCode);

void deleteDictionary(Dictionary **dictionary, int *errorCode);