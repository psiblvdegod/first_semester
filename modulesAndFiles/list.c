#include "list.h"
#include <stdlib.h>
#include <string.h>

typedef struct ListElement {
    Value frequency;
    Key key;
    struct ListElement * previous;
} ListElement;

List createListElement(List list, Key key, Value frequency, bool * errorCode) {
    List newElement = calloc(1, sizeof(ListElement));
    if (newElement == NULL) {
        *errorCode = true;
        return NULL;
    }
    newElement->frequency = frequency;
    newElement->key = key;
    newElement->previous = list;
    return newElement;
}

List updateList(List list, Key key, Value frequency, bool * errorCode) {
    ListElement * listElement = (ListElement *) list;
    while (listElement != NULL) {
        if (strcmp(listElement->key, key) == 0) {
            listElement->frequency += frequency;
            return list;
        }
        listElement = listElement->previous;
    }
    return createListElement(list, key, frequency, errorCode);
}

List getPrevious(List list) {
    if (list == NULL) {
        return NULL;
    }
    return list->previous;
}

int getFrequency(List list, bool * errorCode) {
    if (list == NULL) {
        *errorCode = true;
        return -1;
    }
    return list->frequency;
}

Key getKey(List list, bool * errorCode) {
    if (list == NULL) {
        *errorCode = true;
        return NULL;
    }
    return list->key;
}