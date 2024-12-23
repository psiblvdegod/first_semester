#include "list.h"
#include <string.h>
#include <stdlib.h>

#define INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION 1
#define MEMORY_ALLOCATION_ERROR 44
#define TESTS_FAILED_ERROR (-1)
#define NO_ERRORS 0

typedef struct ListElement {
    Value value;
    struct ListElement *next;
} ListElement;

struct List {
    ListElement *head;
    ListElement *tail;
};

List *createList(int *errorCode) {
    List *list = calloc(1, sizeof(struct List));
    if (list == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }
    return list;
}

void addToList(List *list, Value value, int *errorCode) {
    if (list == NULL || value == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    ListElement *newElement = calloc(1, sizeof(ListElement));
    if (newElement == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return;
    }
    newElement->value = value;
    if (list->head == NULL) {
        list->head = newElement;
        list->tail = newElement;
        return;
    }
    list->tail->next = newElement;
    list->tail = newElement;
}

void addAElements(List *list, const char symbol, int *errorCode) {
    if (list == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    ListElement *currentElement = list->head;
    while (currentElement != NULL) {
        if (currentElement->value[0] == symbol) {
            addElement(list, currentElement->value, errorCode);
        }
    }
}

Value popFromList(List *list, int *errorCode) {
    if (list == NULL || list->head == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return NULL;
    }
    Value result = list->head->value;
    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
        return result;
    }
    list->head = list->head->next;
    return result;
}

void deleteList(List **list, int *errorCode) {
    if (list == NULL || *list == NULL) {
        *errorCode = 1;
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
