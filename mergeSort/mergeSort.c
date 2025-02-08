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

void mergeTwoNodes(List *list, Node **first, Node **second, int *errorCode) {
    while (*first != NULL && *second != NULL) {
        if (strcmp(getKey(*first, errorCode), getKey(*second, errorCode)) < 0) {
            addNode(list, *first, errorCode);
            *first = getNext(*first, errorCode);
        }
        else {
            addNode(list, *second, errorCode);
            *second = getNext(*second, errorCode);
        }
        if (*errorCode != NO_ERRORS) {
            return;
        }
    }
}

void mergeOneNode(List *list, Node **node, int *errorCode) {
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
    mergeTwoNodes(mergedList, &firstNode, &secondNode, errorCode);
    if (*errorCode != NO_ERRORS) {
        return NULL;
    }
    mergeOneNode(mergedList, &firstNode, errorCode);
    if (*errorCode != NO_ERRORS) {
        return NULL;
    }
    mergeOneNode(mergedList, &secondNode, errorCode);
    if (*errorCode != NO_ERRORS) {
        return NULL;
    }
    return mergedList;
}

List *mergeSort(List *list, int *errorCode) {
    if (getHead(list, errorCode) == NULL || getNext(getHead(list, errorCode), errorCode) == NULL) {
        return list;
    }
    List *separatedPart = splitList(list, errorCode);
    if (*errorCode != NO_ERRORS) {
        return NULL;
    }
    list = mergeSort(list, errorCode);
    if (*errorCode != NO_ERRORS) {
        return NULL;
    }
    separatedPart = mergeSort(separatedPart, errorCode);
    if (*errorCode != NO_ERRORS) {
        return NULL;
    }
    return merge(list, separatedPart, errorCode);
}