#include "parse.h"
#include <stdlib.h>

Tree * buildTree(FILE * stream, bool * errorCode) {

    typedef enum {
        digit,
        operation,
    } ValueType;

    Tree * tree = NULL;
    Stack * stack = createStack(errorCode);

    while (!feof(stream)) {
        Node * node = NULL;
        int valueFromStream = getc(stream);
        ValueType valueType;
        if (valueFromStream == ' ' || valueFromStream == '(' || valueFromStream == ')') {
            continue;
        }
        if ('0' <= valueFromStream && valueFromStream <= '9') {
            ungetc(valueFromStream, stream);
            fscanf(stream, "%d", &valueFromStream);
            valueType = digit;
        }
        else {
            valueType = operation;
        }

        node = createNode(valueFromStream, errorCode);

        if (tree == NULL) {
            tree = createTree(node, errorCode);
            push(stack, node, errorCode);
            continue;
        }

        Node * previousOperation = getHead(stack, errorCode);
        Node * leftChild = getChild(previousOperation, left, errorCode);
        Node * rightChild = getChild(previousOperation, right, errorCode);

        bool addChildFlag = false; // no elif xDD
        if (leftChild == NULL) {
            addChild(previousOperation, node, left, errorCode);
            addChildFlag = true;
        }
        if (rightChild == NULL && !addChildFlag) {
            addChild(previousOperation, node, right, errorCode);
            pop(stack, errorCode);
            addChildFlag = true;
        }
        if (valueType == operation) {
            push(stack, node, errorCode);
        }
    }
    return tree;
}

void printAllNodes(Node * node, bool * errorCode) {
    if (node == NULL) {
        return;
    }
    if (getChild(node, left, errorCode) != NULL) {
        printf("%c ", getValue(node, errorCode));
    }
    else {
        printf("%d ", getValue(node ,errorCode));
    }
    printAllNodes(getChild(node, left, errorCode), errorCode);
    printAllNodes(getChild(node, right, errorCode), errorCode);
}

void calculateTreeExample(Node * node, Value lastValue, int currentValue, bool * errorCode) {
    if (node == NULL) {
        return;
    }
    int operand1, operand2;
    char operation;
    if (getChild(node, left, errorCode) == NULL) {
        operand1 = currentValue;
        operation = (char) lastValue;
        operand2 = getValue(node, errorCode);
    }
    else {

    }
    printAllNodes(getChild(node, left, errorCode), errorCode);
    printAllNodes(getChild(node, right, errorCode), errorCode);
}
