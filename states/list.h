#pragma once
#include <stdbool.h>
#include <stdlib.h>

typedef struct List List;

typedef struct ListElement ListElement;

typedef size_t Value;

List *createList(int *errorCode);

void deleteList(List **list, int *errorCode);

void addToList(List *list, Value number, Value distance, int *errorCode);

bool searchInList(List *list, Value value, int *errorCode);

List *copyList(List *list, int *errorCode);

void printList(List *list, int *errorCode);

Value getNumber(ListElement* listElement, int *errorCode);

Value getDistance(ListElement* listElement, int *errorCode);

ListElement *getHead(List *list, int *errorCode);

ListElement *getNext(ListElement* listElement, int *errorCode);

