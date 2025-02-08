#pragma once
#include <stdbool.h>

typedef struct List List;

typedef char *Value;

// creates empty list
List *createList(int *errorCode);

// adds element to the end of the list
void addToList(List *list, Value value, int *errorCode);

// adds to the end of the list all string from the source list starting with symbol
void copyListElementsByFirstSymbol(List *list, char symbol, int *errorCode);

// deletes element from the begging of the list
Value popFromList(List *list, int *errorCode);

// frees allocated memory and turns pointer to NULL
void deleteList(List **list, int *errorCode);

// returns true is list is empty,
// else returns false
bool isEmpty(List *list, int *errorCode);

void deleteOddIndexes(List *list, int *errorCode);