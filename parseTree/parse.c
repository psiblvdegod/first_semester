#include "errorCode.h"
#include "parse.h"
#include <errno.h>
#include <stdlib.h>

typedef enum {
    insignificant,
    incorrect,
    operation,
    number,
} TokenType;

int getToken(FILE *file, TokenType *type, int *errorCode) {
    int token = getc(file);
    if (token == '-') {
        int next = getc(file);
        if ('0' <= next && next <= '9') {
            ungetc(next, file);
            ungetc(token, file);
            fscanf(file, "%d", &token);
            *type = number;
        }
        else {
            *type = operation;
        }
    }
    if ('0' <= token && token <= '9') {
        ungetc(token, file);
        fscanf(file, "%d", &token);
        *type = number;
    }
    else if (token == ' ' || token == '\n' || token == '\t' || token == '(' || token == ')') {
        *type = insignificant;
    }
    else if (token == '+' || token == '*' || token == '/') {
        *type = operation;
    }
    else {
        *type = incorrect;
        *errorCode = INCORRECT_EXPRESSION_IN_FILE;
    }
    return token;
}

Node *buildTree(const char *filePath, int *errorCode) {
    if (filePath == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return nullptr;
    }
    FILE *file = fopen(filePath, "r");
    if (file == nullptr) {
        *errorCode = FILE_OPENING_ERROR;
        return nullptr;
    }
    Node *root = nullptr;
    Stack stack = nullptr;

    while (!feof(file)) {
        TokenType type = 0;
        const int token = getToken(file, &type, errorCode);
        if (*errorCode != NO_ERRORS) {
            break;
        }
        if (type == insignificant) {
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
        Node *operator = getHead(stack, errorCode);
        if (getChild(operator, left, errorCode) == NULL) {
            addChild(operator, node, left, errorCode);
        }
        else {
            addChild(operator, node, right, errorCode);
            pop(&stack, errorCode);
        }
        if (type == operation) {
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
        default:
            *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
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