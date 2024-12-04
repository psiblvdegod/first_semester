#pragma once
#include <stdbool.h>

//ListElement stores key, frequency and previous element.
typedef struct ListElement * List;

typedef const char * Key;

typedef int Value;

//creates and adds element to list.
//list may be NULL.
List createListElement(List list, Key key, Value frequency, bool * errorCode);


//if there is element with such key in the list increases frequency.
//else adds element making frequency = 1.
List updateList(List list, Key key, Value frequency, bool * errorCode);

List getPrevious(List list);

//makes *errorCode true if list is NULL
int getFrequency(List list, bool * errorCode);

//makes *errorCode true if list is NULL
Key getKey(List list, bool * errorCode);
