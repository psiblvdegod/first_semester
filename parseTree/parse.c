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

void doSymmetricalTraversal(Node * node, Node * traversalResult[], int * index, bool * errorCode) {
    if (node == NULL) {
        return;
    }
    doSymmetricalTraversal(getChild(node, left), traversalResult, index, errorCode);
    traversalResult[*index] = node;
    ++(*index);
    doSymmetricalTraversal(getChild(node, right), traversalResult, index, errorCode);
}

int calculateTreeExample(Tree * tree, bool * errorCode) {
    Node * root = getRoot(tree);
    if (tree == NULL || root == NULL) {
        *errorCode = true;
        return -1;
    }
    Node ** traversalResult = malloc(sizeof(tree));
    int traversalResultLength = 0;
    if (traversalResult == NULL) {
        *errorCode = true;
        return -1;
    }
    doSymmetricalTraversal(root, traversalResult, &traversalResultLength, errorCode);
    int calculatingResult = getValue(traversalResult[0], errorCode);
    for (int i = 2; i < traversalResultLength; ++i) {
        int operand = getValue(traversalResult[i], errorCode);
        int operation = getValue(traversalResult[i-1], errorCode);
        switch(operation) {
            case '+':
                calculatingResult += operand;
                break;
            case '-':
                calculatingResult -= operand;
                break;
            case '*':
                calculatingResult *= operand;
                break;
            case '/':
                calculatingResult /= operand;
                break;
            default:
                continue;
        }
    }
    return calculatingResult;
}