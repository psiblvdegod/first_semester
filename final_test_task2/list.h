#pragma once
#include <stdbool.h>

typedef struct List List;

typedef char *Value;

List *createList(int *errorCode);

void addToList(List *list, Value value, int *errorCode);

void addAElements(List *list, char symbol, int *errorCode);

Value popFromList(List *list, int *errorCode);

void deleteList(List **list, int *errorCode);