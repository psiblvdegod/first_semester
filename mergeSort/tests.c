#include "tests.h"
#include <stdio.h>

bool mergeTest() {
    Node firstNode = NULL;
    Node secondNode = NULL;
    bool errorCode = false;
    Value contact1 = {"123", "1"};
    Value contact2 = {"234", "2"};
    Value contact3 = {"345", "3"};
    Value contact4 = {"456", "4"};
    firstNode =  addElement(firstNode, contact1, &errorCode);
    firstNode =  addElement(firstNode, contact3, &errorCode);
    secondNode = addElement(secondNode, contact2, &errorCode);
    secondNode = addElement(secondNode, contact4, &errorCode);
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