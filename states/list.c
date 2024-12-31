#include "errorCode.h"
#include "list.h"
#include <stdio.h>
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
        return NULL;
    }
    return list;
}

void deleteList(List **list, int *errorCode) {
    if (list == NULL || *list == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    ListElement *currentElement = (*list)->head;
    while (currentElement != NULL) {
        ListElement *temp = currentElement;
        currentElement = currentElement->next;
        free(temp);
    }
    free(*list);
    *list = NULL;
}

void addToList(List *list, Value number, Value distance, int *errorCode) {
    if (list == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    ListElement *newElement = calloc(1, sizeof(ListElement));
    if (newElement == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return;
    }
    newElement->number = number;
    newElement->distance = distance;
    newElement->next = list->head;
    list->head = newElement;
}

List *copyList(List *list, int *errorCode) {
    if (list == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return NULL;
    }
    List *copy = createList(errorCode);
    if (*errorCode != NO_ERRORS) {
        return NULL;
    }
    ListElement *current = list->head;
    while (current != NULL) {
        addToList(copy, current->number, current->distance, errorCode);
        if (*errorCode != NO_ERRORS) {
            deleteList(&copy, errorCode);
            return NULL;
        }
        current = current->next;
    }
    return copy;
}

bool searchInList(List *list, Value number, int *errorCode) {
    if (list == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return false;
    }
    ListElement *current = list->head;
    while (current != NULL) {
        if (current->number == number) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void printList(List *list, int *errorCode) {
    if (list == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    ListElement *current = list->head;
    while (current != NULL) {
        printf("%zu ", current->number);
        current = current->next;
    }
}

ListElement *getHead(List *list, int *errorCode) {
    if (list == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return 0;
    }
    return list->head;
}

ListElement *getNext(ListElement* listElement, int *errorCode) {
    if (listElement == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return 0;
    }
    return listElement->next;
}

Value getNumber(ListElement* listElement, int *errorCode) {
    if (listElement == NULL) {
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