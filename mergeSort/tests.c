#include "tests.h"
#include "list.h"
#include "mergeSort.h"
#include "errorCode.h"
#include "contactsSorting.h"
#include <string.h>

void listTests(int *errorCode) {
    List *list = createList(errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    addToList(list, "1", "A", errorCode);
    if (*errorCode != NO_ERRORS) {
        deleteList(&list, errorCode);
        return;
    }
    addToList(list, "2", "B", errorCode);
    addToList(list, "3", "C", errorCode);
    addToList(list, "4", "D", errorCode);
    addToList(list, "5", "E", errorCode);
    if (*errorCode != NO_ERRORS) {
        deleteList(&list, errorCode);
        return;
    }
    Node *node = getHead(list, errorCode);
    if (*errorCode != NO_ERRORS) {
        deleteList(&list, errorCode);
        return;
    }
    const bool test1 = strcmp(getValue(node, errorCode), "1") == 0;
    node = getNext(node, errorCode);
    const bool test2 = strcmp(getKey(node, errorCode), "B") == 0;
    if (*errorCode != NO_ERRORS) {
        deleteList(&list, errorCode);
        return;
    }
    if (!test1 || !test2) {
        *errorCode = TESTS_FAILED_ERROR;
        return;
    }
    List *separatedPart = splitList(list, errorCode);
    if (*errorCode != NO_ERRORS) {
        deleteList(&list, errorCode);
        return;
    }
    const char *expectedResult[] = {"A", "B", "C", "D", "E"};
    Node *current = getHead(list, errorCode);
    int i = 0;
    while (current != NULL) {
        if (strcmp(getKey(current, errorCode), expectedResult[i]) != 0) {
            if (*errorCode == NO_ERRORS) {
                *errorCode = TESTS_FAILED_ERROR;
            }
        }
        current = getNext(current, errorCode);
        ++i;
        if (*errorCode != NO_ERRORS) {
            break;
        }
    }
    current = getHead(separatedPart, errorCode);
    while (current != NULL) {
        if (strcmp(getKey(current, errorCode), expectedResult[i]) != 0) {
            if (*errorCode == NO_ERRORS) {
                *errorCode = TESTS_FAILED_ERROR;
            }
        }
        current = getNext(current, errorCode);
        ++i;
        if (*errorCode != NO_ERRORS) {
            break;
        }
    }
    deleteList(&list, errorCode);
    deleteList(&separatedPart, errorCode);
}

void mergeTest(int *errorCode) {
    List *firstList = createList(errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    List *secondList = createList(errorCode);
    if (*errorCode != NO_ERRORS) {
        deleteList(&firstList, errorCode);
        return;
    }
    addToList(firstList, "abc", "100", errorCode);
    addToList(firstList, "cde", "300", errorCode);
    addToList(secondList, "bcd", "200", errorCode);
    addToList(secondList, "def", "400", errorCode);
    addToList(secondList, "efg", "500", errorCode);
    if (*errorCode != NO_ERRORS) {
        deleteList(&firstList, errorCode);
        deleteList(&secondList, errorCode);
        return;
    }
    List *mergedList = merge(firstList, secondList, errorCode);
    if (*errorCode != NO_ERRORS) {
        deleteList(&firstList, errorCode);
        deleteList(&secondList, errorCode);
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
        if (*errorCode != NO_ERRORS) {
            break;
        }
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
        deleteList(&list, errorCode);
        return;
    }
    list = mergeSort(list, errorCode);
    if (*errorCode != NO_ERRORS) {
        deleteList(&list, errorCode);
        return;
    }
    const char *expectedResult[] = {"1", "1", "1", "2", "2", "2", "3", "3", "4", "4", "5", "8"};
    Node *current = getHead(list, errorCode);
    for (int i = 0; current != NULL; ++i) {
        if (strcmp(getValue(current, errorCode), expectedResult[i]) != 0) {
            if (*errorCode == NO_ERRORS) {
                *errorCode = TESTS_FAILED_ERROR;
            }
        }
        current = getNext(current, errorCode);
        if (*errorCode != NO_ERRORS) {
            break;
        }
    }
    deleteList(&list, errorCode);
}

void contactsSortingTest(const char *filePath, int *errorCode) {
    List *result = sortContacts(filePath, byName, errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    const char *expectedResult[] = {"001", "002", "003", "004", "005"};
    Node *current = getHead(result, errorCode);
    for (int i = 0; current != NULL; ++i) {
        if (strcmp(getValue(current, errorCode), expectedResult[i]) != 0) {
            if (*errorCode == NO_ERRORS) {
                *errorCode = TESTS_FAILED_ERROR;
            }
        }
        current = getNext(current, errorCode);
        if (*errorCode != NO_ERRORS) {
            break;
        }
    }
    deleteList(&result, errorCode);
}