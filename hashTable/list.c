#include "list.h"
#include <stdlib.h>
#include <string.h>

typedef struct ListElement {
    int frequency;
    Key key;
    struct ListElement * previous;
} ListElement;

List * addElementToList(List * list, Key key, bool * errorCode) {
    ListElement * newElement = calloc(1, sizeof(ListElement));
    if (newElement == NULL) {
        *errorCode = true;
        return NULL;
    }
    newElement->frequency = 1;
    newElement->key = key;
    newElement->previous = list;
    return (List *)newElement;
}

List * updateListByKey(List * list, Key key, bool * errorCode) {
    ListElement * listElement = (ListElement *) list;
    while (listElement != NULL) {
        if (strcmp(listElement->key, key) == 0) {
            listElement->frequency += 1;
            return list;
        }
        listElement = listElement->previous;
    }
    list = addElementToList(list, key, errorCode);
    return list;
}

List * getPrevious(List * list) {
    if (list == NULL) {
        return NULL;
    }
    return ((ListElement *) list->previous);
}

int getFrequency(List * list, bool * errorCode) {
    if (list == NULL) {
        *errorCode = true;
        return -1;
    }
    return ((ListElement *) list)->frequency;
}

Key getKey(List * list, bool * errorCode) {
    if (list == NULL) {
        *errorCode = true;
        return NULL;
    }
    return ((ListElement *) list)->key;
}