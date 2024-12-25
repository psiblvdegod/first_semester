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
    addToList(list1, "110", "110", errorCode);
    addToList(list2, "200", "200", errorCode);
    addToList(list2, "220", "220", errorCode);
    addToList(list2, "222", "222", errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    merge(getHead(list1, errorCode), getHead(list2, errorCode), errorCode);
}

bool mergeSortTest() {
    bool errorCode = false;
    Node node = NULL;
    node = addElement(node, (Contact) {"qwe", "222"}, &errorCode);
    node = addElement(node, (Contact) {"asd", "111"}, &errorCode);
    node = addElement(node, (Contact) {"zxc", "333"}, &errorCode);
    node = mergeSort(node, &errorCode);
    bool test1 = !strcmp(getValue(node, &errorCode).value, "111");
    bool test2 = !strcmp(getValue(getNext(node, &errorCode), &errorCode).value, "222");
    bool test3 = !strcmp(getValue(getNext(getNext(node, &errorCode), &errorCode), &errorCode).value, "333");
    return test1 && test2 && test3 && !errorCode;
}