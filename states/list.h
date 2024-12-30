#pragma once
#include <stdbool.h>
#include <stdlib.h>

typedef struct List List;

typedef struct ListElement ListElement;

typedef size_t Value;

List *createList(int *errorCode);

void deleteList(List **list, int *errorCode);

void insertInList(List *list, Value number, Value distance, int *errorCode);

Value popFromList(List *list, int *errorCode);

bool searchInList(List *list, Value value, int *errorCode);

List *copyList(List *list, int *errorCode);

Value getNumber(ListElement* listElement, int *errorCode);

bool isListEmpty(List *list, int *errorCode);

void mergeLists(List *recipient, List *donor, int *errorCode);

void printList(List *list, int *errorCode);