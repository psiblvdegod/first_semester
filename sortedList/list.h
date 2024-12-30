#pragma once
#include <stdbool.h>
#define VALUE_SIZE 50

typedef struct List List;

typedef char *Value;

// creates empty list
List *createList(int *errorCode);

// adds element to list keeping it sorted.
// returns true if element has been added successfully,
// else returns false; definitely some error happened.
bool insertInList(List *list, Value value, int *errorCode);

// deletes element from list keeping it sorted.
// returns true if element has been deleted successfully,
// else returns false; verify errorCode.
bool deleteFromList(List *list, Value value, int *errorCode);

// returns true if there is such value in the list,
// else returns false.
bool searchInList(List *list, Value value, int *errorCode);

// prints all elements from the list.
void printList(List *list, int *errorCode);

// frees memory allocated for the list and turns pointer NULL.
void deleteList(List **list, int *errorCode);

