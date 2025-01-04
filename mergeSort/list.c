#include "list.h"
#include "errorCode.h"
#include <string.h>
#include <stdlib.h>

typedef struct Node {
    Value value;
    Value key;
    struct Node *next;
} Node;

struct List {
    Node *head;
    Node *tail;
};

List *createList(int *errorCode) {
    List *list = calloc(1, sizeof(struct List));
    if (list == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }
    return list;
}

void addToList(List *list, Value value, Value key, int *errorCode) {
    if (list == NULL || value == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    Node *newElement = calloc(1, sizeof(Node));
    if (newElement == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return;
    }
    newElement->value = strdup(value);
    if (newElement->value == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        free(newElement);
        return;
    }
    newElement->key = strdup(key);
    if (newElement->key == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        free(newElement->value);
        free(newElement);
        return;
    }
    if (list->head == NULL) {
        list->head = newElement;
        list->tail = newElement;
        return;
    }
    list->tail->next = newElement;
    list->tail = newElement;
}

List *splitList(List *list, int *errorCode) {
    if (list == NULL || list->head == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return NULL;
    }
    if (list->head == list->tail) {
        return NULL;
    }
    Node *current = getHead(list, errorCode);
    int listLength = 1;
    while(current != NULL) {
        ++listLength;
        current = current->next;
    }
    Node *middle = getHead(list, errorCode);
    for (int i = 1; i < listLength / 2; ++i) {
        middle = middle->next;
    }
    List *separatedPart = createList(errorCode);
    if (*errorCode != NO_ERRORS) {
        return list;
    }
    Node *newHead = middle->next;
    middle->next = NULL;
    separatedPart->head = newHead;
    separatedPart->tail = list->tail;
    list->tail = middle;
    return separatedPart;
}

Node *getHead(List *list, int *errorCode) {
    if (list == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return NULL;
    }
    return list->head;
}

Node *getNext(Node *node, int *errorCode) {
    if (node == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return NULL;
    }
    return node->next;
}

Value getKey(Node *node, int *errorCode) {
    if (node == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return NULL;
    }
    return node->key;
}

Value getValue(Node *node, int *errorCode) {
    if (node == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return NULL;
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