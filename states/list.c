#include "errorCode.h"
#include "list.h"
#include <string.h>
#include <stdlib.h>

struct ListElement {
    Value number;
    Value distance;
    struct ListElement *next;
};

struct List {
    ListElement *head;
};

List *createList(int *errorCode) {
    List *list = calloc(1, sizeof(List));
    if (list == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return nullptr;
    }
    return list;
}

void deleteList(List **list, int *errorCode) {
    if (list == nullptr || *list == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    ListElement *currentElement = (*list)->head;
    while (currentElement != nullptr) {
        ListElement *temp = currentElement;
        currentElement = currentElement->next;
        free(temp);
    }
    free(*list);
    *list = nullptr;
}

void addToList(List *list, Value number, Value distance, int *errorCode) {
    if (list == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    ListElement *newElement = calloc(1, sizeof(ListElement));
    if (newElement == nullptr) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return;
    }
    newElement->number = number;
    newElement->distance = distance;
    newElement->next = list->head;
    list->head = newElement;
}

List *copyList(List *list, int *errorCode) {
    if (list == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return nullptr;
    }
    List *copy = createList(errorCode);
    if (*errorCode != NO_ERRORS) {
        return nullptr;
    }
    ListElement *current = list->head;
    while (current != nullptr) {
        addToList(copy, current->number, current->distance, errorCode);
        if (*errorCode != NO_ERRORS) {
            deleteList(&copy, errorCode);
            return nullptr;
        }
        current = current->next;
    }
    return copy;
}

bool searchInList(List *list, Value number, int *errorCode) {
    if (list == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return false;
    }
    ListElement *current = list->head;
    while (current != nullptr) {
        if (current->number == number) {
            return true;
        }
        current = current->next;
    }
    return false;
}

ListElement *getHead(List *list, int *errorCode) {
    if (list == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return nullptr;
    }
    return list->head;
}

ListElement *getNext(ListElement* listElement, int *errorCode) {
    if (listElement == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return nullptr;
    }
    return listElement->next;
}

Value getNumber(ListElement* listElement, int *errorCode) {
    if (listElement == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return 0;
    }
    return listElement->number;
}

Value getDistance(ListElement* listElement, int *errorCode) {
    if (listElement == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return 0;
    }
    return listElement->distance;
}