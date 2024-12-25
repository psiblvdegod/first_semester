#include "tests.h"
#include "errorCode.h"
#include <string.h>

void mergeTest(int *errorCode) {
    List *list1 = createList(errorCode);
    List *list2 = createList(errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    addToList(list1, "abc", "100", errorCode);
    addToList(list1, "cde", "300", errorCode);
    addToList(list2, "bcd", "200", errorCode);
    addToList(list2, "def", "400", errorCode);
    addToList(list2, "efg", "500", errorCode);
    if (*errorCode != NO_ERRORS) {
            return;
    }
    Node *mergedList = merge(getHead(list1, errorCode), getHead(list2, errorCode), errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    const char *expectedResult[] = {"100", "200", "300", "400", "500"};
    for (int i = 0; mergedList != NULL; ++i) {
        if (strcmp(getKey(mergedList, errorCode), expectedResult[i]) != 0) {
            if (*errorCode == NO_ERRORS) {
                *errorCode = TESTS_FAILED_ERROR;
            }
        }
        mergedList = getNext(mergedList, errorCode);
    }
    deleteList(&list1, errorCode);
    deleteList(&list2, errorCode);
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
    Node *sorted = mergeSort(getHead(list, errorCode), errorCode);
    const char *expectedResult[] = {"1", "1", "1", "2", "2", "2", "3", "3", "4", "4", "5", "8"};
    for (int i = 0; sorted != NULL; ++i) {
        if (strcmp(getValue(sorted, errorCode), expectedResult[i]) != 0) {
            if (*errorCode == NO_ERRORS) {
                *errorCode = TESTS_FAILED_ERROR;
            }
        }
        sorted = getNext(sorted, errorCode);
    }
    deleteList(&list, errorCode);
}
