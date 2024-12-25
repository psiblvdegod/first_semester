#include "tests.h"
#include "errorCode.h"
#include <string.h>

void mergeTest(int *errorCode) {
    List *firstList = createList(errorCode);
    List *secondList = createList(errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    addToList(firstList, "abc", "100", errorCode);
    addToList(firstList, "cde", "300", errorCode);
    addToList(secondList, "bcd", "200", errorCode);
    addToList(secondList, "def", "400", errorCode);
    addToList(secondList, "efg", "500", errorCode);
    if (*errorCode != NO_ERRORS) {
            return;
    }
    List *mergedList = merge(firstList, secondList, errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    const char *expectedResult[] = {"100", "200", "300", "400", "500"};
    Node *current = getHead(mergedList, errorCode);
    for (int i = 0; current != NULL; ++i) {
        if (strcmp(getKey(current, errorCode), expectedResult[i]) != 0) {
            if (*errorCode == NO_ERRORS) {
                *errorCode = TESTS_FAILED_ERROR;
            }
        }
        current = getNext(current, errorCode);
    }
    deleteList(&firstList, errorCode);
    deleteList(&secondList, errorCode);
}

void mergeSortTest(int *errorCode) {
    List *list = createList(errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    addToList(list, "1", "100", errorCode);
    addToList(list, "3", "300", errorCode);
    addToList(list, "2", "200", errorCode);
    addToList(list, "4", "400", errorCode);
    addToList(list, "5", "500", errorCode);
    addToList(list, "1", "100", errorCode);
    addToList(list, "8", "800", errorCode);
    addToList(list, "2", "200", errorCode);
    addToList(list, "4", "400", errorCode);
    addToList(list, "3", "300", errorCode);
    addToList(list, "1", "100", errorCode);
    addToList(list, "2", "200", errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    list = mergeSort(list, errorCode);
    const char *expectedResult[] = {"1", "1", "1", "2", "2", "2", "3", "3", "4", "4", "5", "8"};
    Node *current = getHead(list, errorCode);
    for (int i = 0; current != NULL; ++i) {
        if (strcmp(getValue(current, errorCode), expectedResult[i]) != 0) {
            if (*errorCode == NO_ERRORS) {
                *errorCode = TESTS_FAILED_ERROR;
            }
        }
        current = getNext(current, errorCode);
    }
    deleteList(&list, errorCode);
}
