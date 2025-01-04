#pragma once

#include <stdbool.h>
#include <stdlib.h>

typedef struct List List;

typedef struct ListElement ListElement;

typedef size_t Value;

// creates empty list
List *createList(int *errorCode);

// frees allocated memory, turns pointer NULL
void deleteList(List **list, int *errorCode);

// adds element to list
void addToList(List *list, Value number, Value distance, int *errorCode);

// if there is elements with such number in the list returns true
// else returns false
bool searchInList(List *list, Value number, int *errorCode);

// allocates memory and copies list to it
// returns pointer to list-copy
List *copyList(List *list, int *errorCode);

// returns value from field "number"
Value getNumber(ListElement* listElement, int *errorCode);

// returns value from field "distance"
Value getDistance(ListElement* listElement, int *errorCode);

// returns last element in the list
ListElement *getHead(List *list, int *errorCode);

// if there is next element in the list returns it
// else returns NULL
ListElement *getNext(ListElement* listElement, int *errorCode);

