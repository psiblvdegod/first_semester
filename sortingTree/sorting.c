#include "sorting.h"
#include <stdlib.h>

Node * buildTree(Value *array, const int arraySize, bool * errorCode) {
    Node * root = createNode(array[0], errorCode);
    for (int i = 1; i < arraySize; ++i) {
        Node * newNode = createNode(array[i], errorCode);
        root = insert(root, newNode, errorCode);
    }
    return root;
}

/*
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
*/
/*
int calculateTree(Node * node, bool * errorCode) {
    if (getChild(node, left) == NULL) {
        return getValue(node, errorCode);
    }
    Node * leftChild = getChild(node, left);
    Node * rightChild = getChild(node, right);
    switch(getValue(node, errorCode)) {
        case '+':
            return calculateTree(rightChild, errorCode) + calculateTree(leftChild, errorCode);
        case '-':
            return calculateTree(rightChild, errorCode) - calculateTree(leftChild, errorCode);
        case '*':
            return calculateTree(rightChild, errorCode) * calculateTree(leftChild, errorCode);
        case '/':
            return calculateTree(rightChild, errorCode) / calculateTree(leftChild, errorCode);
    }
}
*/
void treeSort(Node * node, Value * array, int * external, bool * errorCode) {
    if (node == NULL) {
        return;
    }
    printAllNodes(getChild(node, left), array, external, errorCode);
    printf("%s ", getValue(node));
    array[*external] = getValue(node);
    ++(*external);
    printAllNodes(getChild(node, right), array, external, errorCode);
}
