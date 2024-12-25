#include "list.h"
#include "errorCode.h"
#include <string.h>
#include <stdlib.h>

typedef struct Node {
    Value value;
    struct Node *next;
    struct Node *previous;
} Node;

struct List {
    Node *head;
    Node *current;
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
    Node *newElement = calloc(1, sizeof(Node));
    if (newElement == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return;
    }
    newElement->value = value;
    if (list->head == NULL) {
        list->head = newElement;
        list->current = newElement;
        newElement->next = newElement;
        newElement->previous = newElement;
        return;
    }
    newElement->previous = list->current;
    newElement->next -
    list->current->next = newElement;
    list->current = newElement;
}

void deleteCurrent(List *list, int *errorCode) {
    if (list == NULL || list->current == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    Node *temp = list->current;
    if (list->current->next == list->current) {
        list->current = NULL;
        free(temp);
        return;
    }
    list->current->next->previous = list->current->previous;
    list->current->previous->next = list->current->next;
    free(temp);
}

Node *getHead(List *list, int *errorCode) {
    if (list == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return NULL;
    }
    return list->head;
}

Node *getCurrent(List *list, int *errorCode) {
    if (list == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return NULL;
    }
    return list->current;
}

Node *getNext(Node *node, int *errorCode) {
    if (node == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return NULL;
    }
    return node->next;
}

Value getValue(Node *node, int *errorCode) {
    if (node == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return 0;
    }
    return node->value;
}

void deleteList(List **list, int *errorCode) {
    if (list == NULL || *list == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    Node *currentElement = (*list)->head;
    while (currentElement != NULL) {
        Node *temp = currentElement;
        currentElement = currentElement->next;
        free(temp);
    }
    free(*list);
    *list = NULL;
}