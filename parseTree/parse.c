#include "parse.h"
#include <stdlib.h>

Tree * buildTree(FILE * stream, bool * errorCode) {
    Tree * tree = NULL;
    Stack * stack = createStack(errorCode);

    while (!feof(stream)) {
        Node * node = NULL;
        int valueFromStream = getc(stream);
        bool isDigit = false;
        if (valueFromStream == ' ' || valueFromStream == '(' || valueFromStream == ')') {
            continue;
        }
        if ('0' <= valueFromStream && valueFromStream <= '9') {
            ungetc(valueFromStream, stream);
            fscanf(stream, "%d", &valueFromStream);
            isDigit = true;
        }
        node = createNode(valueFromStream, errorCode);
        if (tree == NULL) {
            tree = createTree(node, errorCode);
            push(stack, node, errorCode);
            continue;
        }

        Node * operation = getHead(stack, errorCode);
        Node * leftChild = getChild(operation, left);
        Node * rightChild = getChild(operation, right);

        if (leftChild == NULL) {
            addChild(operation, node, left, errorCode);
        }
        else if (rightChild == NULL) {
            addChild(operation, node, right, errorCode);
            pop(stack, errorCode);
        }
        if (!isDigit) {
            push(stack, node, errorCode);
        }
    }
    return tree;
}

int calculate(Node * node, bool * errorCode) {
    if (getChild(node, left) == NULL) {
        return getValue(node, errorCode);
    }
    Node * leftChild = getChild(node, left);
    Node * rightChild = getChild(node, right);
    switch(getValue(node, errorCode)) {
        case '+':
            return calculate(leftChild, errorCode) + calculate(rightChild, errorCode);
        case '-':
            return calculate(leftChild, errorCode) - calculate(rightChild, errorCode);
        case '*':
            return calculate(leftChild, errorCode) * calculate(rightChild, errorCode);
        case '/':
            return calculate(leftChild, errorCode) / calculate(rightChild, errorCode);
    }
}

void printAllNodes(Node * node, bool * errorCode) {
    if (node == NULL) {
        return;
    }
    if (getChild(node, left) != NULL) {
        printf("%c ", getValue(node, errorCode));
    }
    else {
        printf("%d ", getValue(node ,errorCode));
    }
    printAllNodes(getChild(node, left), errorCode);
    printAllNodes(getChild(node, right), errorCode);
}