#include "list.h"
#include <string.h>
#include <stdlib.h>

#define INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION 1
#define MEMORY_ALLOCATION_ERROR 44
#define TESTS_FAILED_ERROR -1
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

void deleteOddIndexes(List *list, int *errorCode) {
    if (list == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    if (list->head == list->tail) {
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        return;
    }
    ListElement *currentElement = list->head;
    while (currentElement != NULL && currentElement->next != NULL) {
        ListElement *temp = currentElement->next;
        currentElement->next = currentElement->next->next;
        free(temp);
        currentElement = currentElement->next;
    }
}

bool isEmpty(List *list, int *errorCode) {
    if (list == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return true;
    }
    return list->head == NULL;
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