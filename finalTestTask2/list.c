#include "list.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ListElement {
    Value value;
    struct ListElement *next;
} ListElement;

struct List {
    ListElement *head;
};

List *createList(int *errorCode) {
    List *list = calloc(1, sizeof(struct List));
    if (list == NULL) {
        free(list);
        *errorCode = 44;
        return NULL;
    }
    return list;
}

ListElement *insertRecursive(ListElement *current, ListElement *newElement) {
    if (current == NULL || strcmp(newElement->value, current->value) <= 0) {
        newElement->next = current;
        return newElement;
    }
    current->next = insertRecursive(current->next, newElement);
    return current;
}

bool insertInList(List *list, Value value, int *errorCode) {
    if (list == NULL || value == NULL) {
        *errorCode = 1;
        return false;
    }
    ListElement *newElement = calloc(1, sizeof(ListElement));
    if (newElement == NULL) {
        *errorCode = 44;
        free(newElement);
        return false;
    }
    newElement->value = value;
    if (list->head == NULL) {
        list->head = newElement;
        return true;
    }
    list->head = insertRecursive(list->head, newElement);
    return true;
}

ListElement *deleteRecursive(ListElement *current, Value value, bool *isSizeChanged) {
    if (current == NULL || strcmp(value, current->value) < 0) {
        return current;
    }
    if (strcmp(value, current->value) == 0) {
        ListElement *next = current->next;
        free(current);
        *isSizeChanged = true;
        return next;
    }
    current->next = deleteRecursive(current->next, value, isSizeChanged);
    return current;
}

bool deleteFromList(List *list, Value value, int *errorCode) {
    if (list == NULL || value == NULL) {
        *errorCode = 1;
        return false;
    }
    if (list->head == NULL) {
        return false;
    }
    bool isSizeChanged = false;
    list->head = deleteRecursive(list->head, value, &isSizeChanged);
    return isSizeChanged;
}

void printList(List *list, int *errorCode) {
    if (list == NULL) {
        *errorCode = 1;
        return;
    }
    if (list->head == NULL) {
        printf("List is empty.\n");
        return;
    }
    ListElement *current = list->head;
    printf("List:\n");
    while (current != NULL) {
        printf("%s ", current->value);
        current = current->next;
    }
    printf("\n");
}

bool searchInList(List *list, Value value, int *errorCode) {
    if (list == NULL) {
        *errorCode = 1;
        return false;
    }
    ListElement *currentElement = list->head;
    while (currentElement != NULL) {
        if (strcmp(value, currentElement->value) == 0) {
            return true;
        }
        else if (strcmp(value, currentElement->value) > 0) {
            return false;
        }
        currentElement = currentElement->next;
    }
    return false;
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

void addToEnd(List *list, int *errorCode) {
    ListElement *current = list->head;
}