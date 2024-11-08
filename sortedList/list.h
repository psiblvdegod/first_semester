#pragma once

#include <stdbool.h>
#include <stdlib.h>

typedef int Value;

typedef struct ListElement * Position;

typedef struct List List;

List * createList(bool * errorCode);

void addElement(List * list, Position * position, Value value, bool * errorCode);
//after adding moves position on new element


void deleteElement(List * list, Position * position, bool * errorCode);
//after deletion moves position on previous element

int listSize(List * list);

void deleteList(List ** list);

Value getValue(Position position, bool * errorCode);

//Value getValue(List * list, Position * mainPosition, bool * errorCode);

Position getFirst(List * list, bool * errorCode);

Position getLast(List * list, bool * errorCode);

Position getNext(Position position, bool * errorCode);

Position getPrevious(List * list, Position position, bool * errorCode);