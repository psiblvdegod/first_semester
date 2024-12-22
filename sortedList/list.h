#pragma once
#include <stdbool.h>

typedef struct List *List;

typedef char *Value;

List createList(int *errorCode);

bool insertElement(List list, Value value, int *errorCode);

bool deleteElement(List list, Value value, int *errorCode);

void printList(List list, int *errorCode);


void deleteList(List *list, int *errorCode);
