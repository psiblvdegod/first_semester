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
    char * testResult[4] = {"1", "2", "3", "4"};
    for (int i = 0; result != NULL; i++) {
        if (getValue(result, &errorCode).value != testResult[i]) {
            return false;
        }
        result = getNext(result, &errorCode);
    }
    return true;
}