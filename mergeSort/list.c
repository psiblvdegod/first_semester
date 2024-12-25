#include "list.h"
#include <string.h>
#include <stdlib.h>

#define INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION 1
#define MEMORY_ALLOCATION_ERROR 44
#define TESTS_FAILED_ERROR -1
#define NO_ERRORS 0
#define FILE_OPENING_ERROR 15

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
    newElement->value = value;
    newElement->key = key;
    if (list->head == NULL) {
        list->head = newElement;
        list->tail = newElement;
        return;
    }
    list->tail->next = newElement;
    list->tail = newElement;
}

Node *splitList(Node *node, int *errorCode) {
    if (node == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return NULL;
    }
    Node *middle = node;
    int listLength = 0;
    while(node != NULL) {
        ++listLength;
        node = node->next;
    }
    for (int i = 0; i < listLength / 2; ++i) {
        middle = middle->next;
    }
    Node *temp = middle;
    middle = middle->next;
    temp->next = NULL;
    return middle;
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
    Node *currentElement = (*list)->head;
    while (currentElement != NULL) {
        Node *temp = currentElement;
        currentElement = currentElement->next;
        free(temp);
    }
    free(*list);
    *list = NULL;
}