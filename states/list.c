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

ListElement *insertRecursive(ListElement *current, ListElement *newElement) {
    if (current == NULL || newElement->distance <= current->distance) {
        newElement->next = current;
        return newElement;
    }
    current->next = insertRecursive(current->next, newElement);
    return current;
}

void insertInList(List *list, Value number, Value distance, int *errorCode) {
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
    list->head = insertRecursive(list->head, newElement);
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
        insertInList(copy, current->number, current->distance, errorCode);
        if (*errorCode != NO_ERRORS) {
            deleteList(&copy, errorCode);
            return NULL;
        }
        current = current->next;
    }
    return copy;
}

ListElement *popFromList(List *list, int *errorCode) {
    if (list == NULL || list->head == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return NULL;
    }
    ListElement *result = list->head;
    list->head = list->head->next;
    return result;
}

bool searchInList(List *list, Value value, int *errorCode) {
    if (list == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return false;
    }
    ListElement *current = list->head;
    while (current != NULL) {
        if (current->number == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

Value getNumber(ListElement* listElement, int *errorCode) {
    if (listElement == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return 0;
    }
    return listElement->number;
}

bool isListEmpty(List *list, int *errorCode) {
    if (list == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return true;
    }
    return list->head == NULL;
}

void mergeLists(List *recipient, List *donor, int *errorCode) {
    if (recipient == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    if (donor == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    ListElement *current = donor->head;
    while (current != NULL) {
        insertInList(recipient, current->number, current->distance, errorCode);
        current = current->next;
    }
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