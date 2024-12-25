#include "mergeSort.h"
#include "errorCode.h"
#include <string.h>

void addNode(List *list, Node *node, int *errorCode) {
    if (list == NULL || node == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    addToList(list, getValue(node, errorCode), getKey(node, errorCode), errorCode);
}

void mergeTwo(List *list, Node **first, Node **second, int *errorCode) {
    while (*first != NULL && *second != NULL) {
        if (strcmp(getKey(*first, errorCode), getKey(*second, errorCode)) < 0) {
            addNode(list, *first, errorCode);
            *first = getNext(*first, errorCode);
        } else {
            addNode(list, *second, errorCode);
            *second = getNext(*second, errorCode);
        }
        if (*errorCode != NO_ERRORS) {
            return;
        }
    }
}

void mergeOne(List *list, Node **node, int *errorCode) {
    while (*node != NULL) {
        addNode(list, *node, errorCode);
        *node = getNext(*node, errorCode);
        if (*errorCode != NO_ERRORS) {
            return;
        }
    }
}

List *merge(List *firstList, List *secondList, int *errorCode) {
    List *mergedList = createList(errorCode);
    Node *firstNode = getHead(firstList, errorCode);
    Node *secondNode = getHead(secondList, errorCode);
    if (*errorCode != NO_ERRORS) {
        return NULL;
    }
    mergeTwo(mergedList, &firstNode, &secondNode, errorCode);
    if (*errorCode != NO_ERRORS) {
        return NULL;
    }
    mergeOne(mergedList, &firstNode, errorCode);
    if (*errorCode != NO_ERRORS) {
        return NULL;
    }
    mergeOne(mergedList, &secondNode, errorCode);
    if (*errorCode != NO_ERRORS) {
        return NULL;
    }
    return mergedList;
}

List *mergeSort(List *left, int *errorCode) {
    if (getHead(left, errorCode) == NULL || getNext(getHead(left, errorCode), errorCode) == NULL) {
        return left;
    }
    List *right = splitList(left, errorCode);
    if (*errorCode != NO_ERRORS) {
        return NULL;
    }
    left = mergeSort(left, errorCode);
    if (*errorCode != NO_ERRORS) {
        return NULL;
    }
    right = mergeSort(right, errorCode);
    if (*errorCode != NO_ERRORS) {
        return NULL;
    }
    return merge(left, right, errorCode);
}