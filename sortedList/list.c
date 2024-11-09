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
    ListElement * guardian = calloc(1 , sizeof(ListElement));
    if (list == NULL || guardian == NULL) {
        *errorCode = true;
        return NULL;
    }
    guardian->value = 0;
    list->head = guardian;
    guardian->next = guardian;
    guardian->previous = guardian;
    list->listSize = 1;
    return list;
}

int listSize(List * list) {
    return list->listSize;
}

Value getValue(Position position, bool * errorCode) {
    if (position == NULL) {
        *errorCode = true;
        return 0;
    }
    return ((ListElement *)position)->value;
}


Position getNext(Position position, bool * errorCode) {
    if (position == NULL) {
        *errorCode = true;
        return NULL;
    }
    return (Position) ((ListElement *) position)->next;
}

Position getPrevious(List * list, Position position, bool * errorCode) {
    if (position == NULL) {
        *errorCode = true;
        return NULL;
    }
    return (Position) ((ListElement *) position)->previous;
}

Position getGuardian(List * list, bool * errorCode) {
    if (list == NULL) {
        *errorCode = true;
        return NULL;
    }
    return (Position) (list->head);
}

Position getLast(List * list, bool * errorCode) {
    if (list == NULL) {
        *errorCode = true;
        return NULL;
    }
    return (Position) (getGuardian(list, errorCode))->previous;
}

void addElement(List * list, Position position, Value value, bool * errorCode) {
    if (position == NULL) {
        *errorCode = true;
        return;
    }
    position = (ListElement *) position;
    ListElement * newElement = calloc(1, sizeof(ListElement));
    if (newElement == NULL) {
        *errorCode = true;
        return;
    }
    newElement->value = value;
    if (listSize(list) == 0) {
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
    ++list->listSize;
}

void deleteElement(List * list, Position position, bool * errorCode) {
    position = (ListElement *) position;
    if (position == NULL) {
        *errorCode = true;
        return;
    }
    if (position == getGuardian(list, errorCode)) {
        return;
    }
    position->previous->next = position->next;
    position->next->previous = position->previous;
    free(position);
    --list->listSize;
    if (listSize(list) == 0) {
        list->head = NULL;
    }
}

void deleteList(List ** list, bool * errorCode) {
    ListElement * cleaner = getGuardian(*list, errorCode);
    while (listSize(*list)) {
        Position temp = cleaner;
        cleaner = cleaner->next;
        deleteElement(*list, temp, errorCode);
    }
    *list == NULL;
}

