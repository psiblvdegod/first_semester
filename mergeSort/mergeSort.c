#include "mergeSort.h"

Node merge(Node firstNode, Node secondNode, bool * errorCode) {
    Node mergedList = NULL;
    while(firstNode != NULL && secondNode != NULL) {
        char * firstNodeKey = getValue(firstNode, errorCode).key;
        char * secondNodeKey = getValue(secondNode, errorCode).key;
        bool comparisonResult = strcmp(firstNodeKey, secondNodeKey) > 0;
        if (comparisonResult) {
            mergedList = addElement(mergedList, getValue(firstNode, errorCode), errorCode);
            firstNode = getNext(firstNode, errorCode);
        }
        else {
            mergedList = addElement(mergedList, getValue(secondNode, errorCode), errorCode);
            secondNode = getNext(secondNode, errorCode);
        }
    }
    while (firstNode != NULL) {
        mergedList = addElement(mergedList, getValue(firstNode, errorCode), errorCode);
        firstNode = getNext(firstNode, errorCode);
    }
    while (secondNode != NULL) {
        mergedList = addElement(mergedList, getValue(secondNode, errorCode), errorCode);
        secondNode = getNext(secondNode, errorCode);
    }
    return mergedList;
}

Node getMiddle(Node node, bool * errorCode) {
    Node middle = node;
    int listLen = 0;
    while (node != NULL) {
        listLen += 1;
        node = getNext(node, errorCode);
    }
    for (listLen; listLen > 0; listLen -= 2) {
        middle = getNext(middle, errorCode);
    }
    return middle;
}

Node reverse(Node node, bool * errorCode) {
    Node reversedNode = NULL;
    while (node != NULL) {
        reversedNode = addElement(reversedNode, getValue(node, errorCode), errorCode);
        node = getNext(node, errorCode);
    }
    return reversedNode;
}

Node mergeSort(Node head, bool * errorCode) {
    if (getNext(head, errorCode) == NULL) {
        return head;
    }

    Node firstNode = NULL;
    Node secondNode = NULL;
    Node middle = getMiddle(head, errorCode);
    Node tempNode = head;
    while (tempNode != middle) {
        firstNode = addElement(firstNode, getValue(tempNode, errorCode), errorCode);
        tempNode = getNext(tempNode, errorCode);
    }
    while (tempNode != NULL) {
        secondNode = addElement(secondNode, getValue(tempNode, errorCode), errorCode);
        tempNode = getNext(tempNode, errorCode);
    }

    firstNode =  reverse(mergeSort(firstNode, errorCode), errorCode);
    secondNode = reverse(mergeSort(secondNode, errorCode), errorCode);

    return merge(firstNode, secondNode, errorCode);
}

