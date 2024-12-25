#include "mergeSort.h"
#include <string.h>

#define INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION 1
#define MEMORY_ALLOCATION_ERROR 44
#define TESTS_FAILED_ERROR -1
#define NO_ERRORS 0

void addNode(List *list, Node *node, int *errorCode) {
    if (list == NULL || node == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    addToList(list, getValue(node, errorCode), getKey(node, errorCode), errorCode);
}

void mergeTwo(List *list, Node *first, Node *second, int *errorCode) {
    if (list == NULL || first == NULL || second == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    while (first != NULL && second != NULL) {
        if (strcmp(getKey(first, errorCode), getKey(second, errorCode)) < 0) {
            addNode(list, first, errorCode);
            first = getNext(first, errorCode);
        } else {
            addNode(list, second, errorCode);
            second = getNext(second, errorCode);
        }
        if (*errorCode != NO_ERRORS) {
            return;
        }
    }
}

void mergeOne(List *list, Node *node, int *errorCode) {
    if (list == NULL || node == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
    }
    while (node != NULL) {
        addNode(list, node, errorCode);
        node = getNext(node, errorCode);
        if (*errorCode != NO_ERRORS) {
            return;
        }
    }
}

Node *merge(Node *firstNode, Node *secondNode, int *errorCode) {
    List *mergedList = createList(errorCode);
    if (*errorCode != NO_ERRORS) {
        return NULL;
    }
    mergeTwo(mergedList, firstNode, secondNode, errorCode);
    if (*errorCode != NO_ERRORS) {
        return NULL;
    }
    mergeOne(mergedList, firstNode, errorCode);
    if (*errorCode != NO_ERRORS) {
        return NULL;
    }
    mergeOne(mergedList, secondNode, errorCode);
    if (*errorCode != NO_ERRORS) {
        return NULL;
    }
    return getHead(mergedList, errorCode);
}

Node *mergeSort(Node *left, int *errorCode) {
    if (getNext(left, errorCode) == NULL) {
        return left;
    }
    Node *right = splitList(left, errorCode);
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