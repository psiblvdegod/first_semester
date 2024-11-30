#pragma once
#include <stdbool.h>

typedef struct ListElement List;

typedef const char * Key;

List * addElementToList(List * list, Key key, bool * errorCode);

//if there is element with such key in the list increases frequency.
//else adds element making frequency = 1.
List * updateListByKey(List * list, Key key, bool * errorCode);