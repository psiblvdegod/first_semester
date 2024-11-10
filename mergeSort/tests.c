#include "tests.h"

bool mergeTest() {
    Node firstNode = NULL;
    Node secondNode = NULL;
    bool errorCode = false;
    Value contact1 = {"123", "1"};
    Value contact2 = {"234", "2"};
    Value contact3 = {"345", "3"};
    Value contact4 = {"456", "4"};
    firstNode =  addElement(firstNode, contact1, &errorCode);
    firstNode =  addElement(firstNode, contact2, &errorCode);
    secondNode = addElement(secondNode, contact3, &errorCode);
    secondNode = addElement(secondNode, contact4, &errorCode);
    Node result = mergeSort(firstNode, secondNode, &errorCode);
}