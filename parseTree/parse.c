#include "parse.h"
#include "errorCode.h"
#include <errno.h>
#include <stdlib.h>

Node *buildTree(const char *filePath, int *errorCode) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        *errorCode = FILE_OPENING_ERROR;
        return NULL;
    }
    Node *root = NULL;
    Stack stack = NULL;

    while (!feof(file)) {
        int token = getc(file);
        bool isDigit = false;
        if (token == ' ' || token == '(' || token == ')') {
            continue;
        }
        if ('0' <= token && token <= '9') {
            ungetc(token, file);
            fscanf(file, "%d", &token);
            /*
            if (errno != 0) {
                *errorCode = ERROR_INCORRECT_EXPRESSION_IN_FILE;
                break;
            }
             */
            isDigit = true;
        }
        Node *node = createNode(token, errorCode);
        if (*errorCode != NO_ERRORS) {
            break;
        }
        if (root == NULL) {
            root = node;
            push(&stack, node, errorCode);
            if (*errorCode != NO_ERRORS) {
                break;
            }
            continue;
        }

        Node *operation = getHead(stack, errorCode);
        Node *leftChild = getChild(operation, left, errorCode);
        Node *rightChild = getChild(operation, right, errorCode);

        if (leftChild == NULL) {
            addChild(operation, node, left, errorCode);
        }
        else if (rightChild == NULL) {
            addChild(operation, node, right, errorCode);
            pop(&stack, errorCode);
        }
        if (!isDigit) {
            push(&stack, node, errorCode);
        }
        if (*errorCode != NO_ERRORS) {
            break;
        }
    }
    fclose(file);
    if (*errorCode != NO_ERRORS) {
        deleteTree(&root, errorCode);
        deleteStack(&stack, errorCode);
    }
    return root;
}

int calculateTree(Node *node, int *errorCode) {
    if (getChild(node, left, errorCode) == NULL) {
        return getValue(node, errorCode);
    }
    Node *leftChild = getChild(node, left, errorCode);
    Node *rightChild = getChild(node, right, errorCode);
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

void printTree(Node *node, int *errorCode) {
    if (node == NULL) {
        return;
    }
    if (getChild(node, left, errorCode) == NULL) {
        printf("%d ", getValue(node, errorCode));
    }
    else {
        printf("%c ", getValue(node, errorCode));
    }
    printTree(getChild(node, left, errorCode), errorCode);
    printTree(getChild(node, right, errorCode), errorCode);
}