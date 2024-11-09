#include "list.h"

typedef struct ListElement {
    Value value;
    struct ListElement * next;
    struct ListElement * previous;
} ListElement;

struct List {
    ListElement * head;
    int listSize;
};

List * createList(bool * errorCode) {
    List * list = calloc(1, sizeof(List));
    if (list == NULL) {
        *errorCode = true;
        return NULL;
    }
    list->head = NULL;
    list->listSize = 0;
    return list;
}

int listSize(List * list) {
    return list->listSize;
}

Position getNext(Position position, bool * errorCode) {
    return (Position) ((ListElement *) position)->next;
}

Position getPrevious(List * list, Position position, bool * errorCode) {
    return (Position) ((ListElement *) position)->previous;
}

Position getFirst(List * list, bool * errorCode) {
    return (Position) (list->head);
}

Position getLast(List * list, bool * errorCode) {
    return (Position) (getFirst(list, errorCode))->previous;
}

void addElement(List * list, Position * externalPosition, Value value, bool * errorCode) {
    ListElement * position = *externalPosition;
    ListElement * newElement = calloc(1, sizeof(ListElement));
    if (newElement == NULL) {
        *errorCode = true;
        return;
    }
    newElement->value = value;
    if (position == NULL) {
        newElement->next = newElement;
        newElement->previous = newElement;
        list->head = newElement;
    }
    else {
        newElement->previous = position;
        newElement->next = position->next;
        position->next->previous = newElement;
        position->next = newElement;
    }
    *externalPosition = newElement;
    ++list->listSize;
}

void deleteElement(List * list, Position * externalPosition, bool * errorCode) {
    ListElement * position = *externalPosition;
    if (position == NULL) {
        *errorCode = true;
        return;
    }
    position->previous->next = position->next;
    position->next->previous = position->previous;
    if (position == getFirst(list, errorCode)) {
        list->head = position->next;
    }
    if (list->listSize == 1) {
        *externalPosition = NULL;
    }
    free(position);
    --list->listSize;
}

void deleteList(List ** list, bool * errorCode) {
    ListElement * cleaner = getFirst(*list, errorCode);
    while (listSize(*list)) {
        Position temp = cleaner;
        cleaner = cleaner->next;
        deleteElement(*list, &temp, errorCode);
    }
    *list = NULL;
}

Value getValue(Position position, bool * errorCode) {
//    if (position == NULL) {
//        //*errorCode = true;
//        return;
//    }
    return ((ListElement *)position)->value;
}
