#include "mergeSort.h"
#include <string.h>

#define INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION 1
#define MEMORY_ALLOCATION_ERROR 44
#define TESTS_FAILED_ERROR -1
#define NO_ERRORS 0

Node *merge(Node *firstNode, Node *secondNode, int *errorCode) {
    List *mergedList = createList(errorCode);
    if (*errorCode != NO_ERRORS) {
        return NULL;
    }
    while(firstNode != NULL && secondNode != NULL) {
        if (strcmp(getKey(firstNode, errorCode), getKey(secondNode, errorCode)) < 0) {
            addToList(mergedList, getKey(firstNode, errorCode), errorCode);
            firstNode = getNext(firstNode, errorCode)
        }
        else {
            addToList(mergedList, getKey(secondNode, errorCode), errorCode);
            secondNode = getNext(secondNode, errorCode);
        }
        if (*errorCode != NO_ERRORS) {
            return NULL;
        }
    }
    while (firstNode != NULL) {
        addToList(mergedList, getKey(firstNode, errorCode), errorCode);
        firstNode = getNext(firstNode, errorCode);
    }
    while (secondNode != NULL) {
        addToList(mergedList, getKey(secondNode, errorCode), errorCode);
        secondNode = getNext(secondNode, errorCode);
    }
    return mergedList;
}

Node *mergeSortInternals(Node *left, int *errorCode) {
    if (getNext(left, errorCode) == NULL) {
        return left;
    }
    Node *right = splitList(left, errorCode);
    left = mergeSortInternals(left, errorCode);
    right = mergeSortInternals(right, errorCode);

}

List *mergeSort(List *list, int *errorCode) {
    mergeSortInternals(getHead(list, errorCode), errorCode);
}