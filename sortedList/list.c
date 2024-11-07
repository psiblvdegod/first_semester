#include "list.h"

typedef struct ListElement {
    Value value;
    struct ListElement * next;
    struct ListElement * previous;
} ListElement;

struct List {
    ListElement * head;
};

List * createList(bool * errorCode) {
    ListElement * guardian = calloc(1, sizeof(ListElement));
    List * list = calloc(1, sizeof(List));
    if (guardian == NULL || list == NULL) {
        *errorCode = true;
        return NULL;
    }
    guardian->next = NULL;
    guardian->previous == NULL; //мейби не нужно
    list->head = guardian;
    return list;
}

void addElement(List * list, Position * mainPosition, Value value, bool * errorCode) {
    ListElement * position = *mainPosition;
    ListElement * newElement = calloc(1, sizeof(ListElement));
    if (newElement == NULL) {
        *errorCode = true;
        return;
    }
    newElement->value = value;
    if (position != NULL) {
        if (position->next != NULL) {
            position->next->previous = newElement;
        }
        newElement->previous = position;
        newElement->next = position->next;
        position->next = newElement;
    }
    else {
        newElement->previous = list->head;
        newElement->previous->next = newElement;
        newElement->next = NULL; //СКОРЕЕ ВСЕГО НЕ НУЖНО
    }
    *mainPosition = newElement;
}

void deleteElement(Position * mainPosition, bool * errorCode) {
    ListElement * position = *mainPosition;
    if (position == NULL) {
        *errorCode = true;
        return;
    }
    position->previous->next = position->next;
    if (position->next != NULL) {
        position->next->previous = position->previous;
    }
    if (position->previous->previous != NULL) {
        *mainPosition = position->previous;
    }
    else {
        *mainPosition = NULL;
    }
    free(position);
}

bool isEmpty(List * list) {
    return list->head->next == NULL;
}

void deleteList(List ** list) {
    ListElement * cleaner = (*list)->head;
    while (cleaner->next != NULL) {
        ListElement * temp = cleaner;
        cleaner = cleaner->next;
        free(temp);
    }
    *list == NULL;
}

Value getValue(Position position, bool * errorCode) {
    if (position == NULL) {
        *errorCode = true;
        return 0;
    }
    return ((ListElement *)position)->value;
}

//Position getFirst(List * list, bool * errorCode) {
//    return (Position) (list->head->next);
//}

Position getFirst(List * list, bool * errorCode) {
    return (Position) (list->head->next);
}

Position getLast(List * list, bool * errorCode) {
    if (list->head->next == NULL) {
        *errorCode = true;
        return NULL;
    }
    ListElement * lastElement = list->head->next;
    while (lastElement->next != NULL) {
        lastElement = lastElement->next;
    }
    return (Position) lastElement;
}

Position getNext(Position position, bool * errorCode) {
    if (((ListElement *) position)->next == NULL) {
        *errorCode = true;
        return NULL;
    }
    return (Position) ((ListElement *) position)->next;
}

Position getPrevious(List * list, Position position, bool * errorCode) {
    if (((ListElement *) position)->previous == list->head) {
        *errorCode = true;
        return NULL;
    }
    return (Position) ((ListElement *) position)->previous;
}
/*Value getValue(List * list, Position * mainPosition, bool * errorCode) {
    ListElement * position = *mainPosition;
    if (position == NULL) { //помещает на стражнтка если temp только создан
        position = list->head;
        *mainPosition = position; //мейби не нужно
    }
    if (position->next != NULL) {
        Value value = position->next->value;
        *mainPosition = position->next;
    }
    else {
        *errorCode = true;
        return 0;
    }
}*/