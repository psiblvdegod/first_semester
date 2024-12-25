#include "list.h"
#include <stdlib.h>
#include "errorCode.h"

struct Node {
    struct Node *next;
    Value value;
};

struct List {
    Node *head;
    Node *tail;
};

List *createList(int *errorCode) {
    List *list = calloc(1, sizeof(List));
    if (list == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
    }
    return list;
}

void addToList(List *list, Value value, int *errorCode) {
    if (list == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    Node *node = calloc(1, sizeof(Node));
    if (node == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return;
    }
    node->value = value;
    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
        node->next = node;
        return;
    }
    list->tail->next = node;
    list->tail = node;
    node->next = list->head;
}

void deleteNext(Node *node, int *errorCode) {
    if (node == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    Node *temp = node->next;
    node->next = node->next->next;
    free(temp);
}

void deleteList(List **list, int *errorCode) {
    if (list == NULL || *list == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    Node *current = (*list)->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(*list);
    *list = NULL;
}

Node *getNext(Node *node, int *errorCode) {
    if (node == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return NULL;
    }
    return node->next;
}

Node *getHead(List *list, int *errorCode) {
    if (list == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return NULL;
    }
    return list->head;
}

Value getValue(Node *node, int *errorCode) {
    if (node == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return 0;
    }
    return node->value;
}