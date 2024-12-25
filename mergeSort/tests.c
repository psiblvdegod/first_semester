#include "tests.h"
#include "errorCode.h"
#include <stdio.h>

void mergeTest(int *errorCode) {
    List *list1 = createList(errorCode);
    List *list2 = createList(errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    addToList(list1, "100", "100", errorCode);
    addToList(list1, "300", "300", errorCode);
    addToList(list2, "200", "200", errorCode);
    addToList(list2, "400", "400", errorCode);
    addToList(list2, "500", "500", errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    Node *mergedList = merge(getHead(list1, errorCode), getHead(list2, errorCode), errorCode);

}

void mergeSortTest(int *errorCode) {
    List *list = createList(errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    addToList(list, "100", "100", errorCode);
    addToList(list, "300", "300", errorCode);
    addToList(list, "200", "200", errorCode);
    addToList(list, "400", "400", errorCode);
    addToList(list, "500", "500", errorCode);
    addToList(list, "100", "100", errorCode);
    addToList(list, "800", "800", errorCode);
    addToList(list, "200", "200", errorCode);
    addToList(list, "400", "400", errorCode);
    addToList(list, "300", "300", errorCode);
    addToList(list, "100", "100", errorCode);
    addToList(list, "200", "200", errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    Node *sorted = mergeSort(getHead(list, errorCode), errorCode);
    int a = 0;
}
