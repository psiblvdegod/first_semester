#pragma once

#include <stdbool.h>
#include <stdlib.h>

typedef int Value;

typedef struct ListElement * Position;

typedef struct List List;

List * createList(bool * errorCode);

//after adding moves position on new element
void addElement(List * list, Position * position, Value value, bool * errorCode);

//after deletion moves position on previous element
void deleteElement(List * list, Position * position, bool * errorCode);

int listSize(List * list);

void deleteList(List ** list, bool * errorCode);

Value getValue(Position position, bool * errorCode);

//if there is the only one element in the list, these functions return a pointer to it
Position getFirst(List * list, bool * errorCode);
Position getLast(List * list, bool * errorCode);
Position getNext(Position position, bool * errorCode);
Position getPrevious(List * list, Position position, bool * errorCode);