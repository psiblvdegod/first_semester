#include "tests.h"
#include <stdio.h>

bool mergeTest() {
    Node firstNode = NULL;
    Node secondNode = NULL;
    bool errorCode = false;
    Value contact1 = {"a", "1"};
    Value contact2 = {"b", "2"};
    Value contact3 = {"c", "3"};
    Value contact4 = {"d", "4"};
    Value contact5 = {"e", "5"};
    Value contact6 = {"f", "6"};

    firstNode = addElement(firstNode, contact2, &errorCode);
    firstNode = addElement(firstNode, contact5, &errorCode);

    secondNode = addElement(secondNode, contact1, &errorCode);
    secondNode = addElement(secondNode, contact3, &errorCode);
    secondNode = addElement(secondNode, contact4, &errorCode);
    secondNode = addElement(secondNode, contact6, &errorCode);

    Node result = merge(firstNode, secondNode, &errorCode);
    char * testResult[6] = {"1", "2", "3", "4", "5", "6"};
    for (int i = 0; result != NULL; i++) {
        if (getValue(result, &errorCode).value != testResult[i]) {
            return false;
        }
        result = getNext(result, &errorCode);
    }
    return true;
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