#include "mergeSort.h"

Node mergeSort(Node firstNode, Node secondNode, bool * errorCode) {
    Node mergedList = NULL;
    do {
        if (firstNode == NULL) {
            mergedList = addElement(mergedList, getValue(secondNode, errorCode), errorCode);
            secondNode = getPrevious(secondNode, errorCode);
            continue;
        }
        if (secondNode == NULL) {
            mergedList = addElement(mergedList, getValue(firstNode, errorCode), errorCode);
            firstNode = getPrevious(firstNode, errorCode);
            continue;
        }
        char * firstNodeKey = getValue(firstNode, errorCode).key;
        char * secondNodeKey = getValue(secondNode, errorCode).key;
        bool comparisonResult = strcmp(firstNodeKey, secondNodeKey) > 0 ? true : false;
        if (comparisonResult) {
            mergedList = addElement(mergedList, getValue(firstNode, errorCode), errorCode);
            firstNode = getPrevious(firstNode, errorCode);
        }
        else {
            mergedList = addElement(mergedList, getValue(secondNode, errorCode), errorCode);
            secondNode = getPrevious(secondNode, errorCode);
        }
    } while(firstNode != NULL || secondNode != NULL);
    return mergedList;
}