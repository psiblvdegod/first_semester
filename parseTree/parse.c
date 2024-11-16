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

void doSymmetricalTraversal(Node * node, Node * traversalResult[], int * index, bool * errorCode) {
    if (node == NULL) {
        return;
    }
    doSymmetricalTraversal(getChild(node, left, errorCode), traversalResult, index, errorCode);
    traversalResult[*index] = node;
    ++(*index);
    doSymmetricalTraversal(getChild(node, right, errorCode), traversalResult, index, errorCode);
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