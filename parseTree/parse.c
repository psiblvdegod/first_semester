#include "parse.h"
#include "errorCode.h"
#include <errno.h>
#include <stdlib.h>

int getToken(FILE *file, char *type, int *errorCode) {
    int token = getc(file);
    if ('0' <= token && token <= '9') {
        ungetc(token, file);
        fscanf(file, "%d", &token);
        *type = 'd';
    }
    else if (token == ' ' || token == '\n' || token == '\t') {
        *type = 'c';
    }
    else if (token == '+' || token == '-' || token == '*' || token == '/') {
        *type = 'o';
    }
    else {
        *errorCode = INCORRECT_EXPRESSION_IN_FILE;
        *type = 'e';
    }
    return token;
}

Node *buildTree(const char *filePath, int *errorCode) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        *errorCode = FILE_OPENING_ERROR;
        return NULL;
    }
    Node *root = NULL;
    Stack stack = NULL;

    while (!feof(file)) {
        char type = 0;
        int token = getToken(file, &type, errorCode);
        if (*errorCode != NO_ERRORS) {
            break;
        }
        if (type == 'c') {
            continue;
        }
        Node *node = createNode(token, errorCode);
        if (root == NULL) {
            root = node;
            push(&stack, node, errorCode);
            continue;
        }
        if (stack == NULL) {
            *errorCode = INCORRECT_EXPRESSION_IN_FILE;
            break;
        }
        Node *operation = getHead(stack, errorCode);
        if (getChild(operation, left, errorCode) == NULL) {
            addChild(operation, node, left, errorCode);
        }
        else {
            addChild(operation, node, right, errorCode);
            pop(&stack, errorCode);
        }
        if (type == 'o') {
            push(&stack, node, errorCode);
        }
        if (*errorCode != NO_ERRORS) {
            break;
        }
    }
    fclose(file);
    if (stack != NULL) {
        *errorCode = INCORRECT_EXPRESSION_IN_FILE;
        deleteStack(&stack, errorCode);
    }
    if (*errorCode != NO_ERRORS) {
        deleteTree(&root, errorCode);
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