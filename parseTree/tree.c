#include "errorCode.h"
#include "tree.h"
#include <stdlib.h>

typedef struct Node {
    Value value;
    struct Node *leftChild;
    struct Node *rightChild;
} Node;

Node *createNode(Value value, int *errorCode) {
    Node *node = calloc(1, sizeof(Node));
    if (node == nullptr) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return nullptr;
    }
    node->value = value;
    return node;
}

void addChild(Node *parent, Node *child, Position position, int *errorCode) {
    if (parent == nullptr || child == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    if (position == left) {
        parent->leftChild = child;
    }
    else {
        parent->rightChild = child;
    }
}

Node *getChild(Node *parent, Position position, int *errorCode) {
    if (parent == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return nullptr;
    }
    if (position == left) {
        return parent->leftChild;
    }
    else {
        return parent->rightChild;
    }
}

Value getValue(Node *node, int *errorCode) {
    if (node == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return '\0';
    }
    return node->value;
}

void freeNodes(Node *node, int *errorCode) {
    if (node == nullptr) {
        return;
    }
    freeNodes(getChild(node, left, errorCode), errorCode);
    freeNodes(getChild(node, right, errorCode), errorCode);
    free(node);
}

void deleteTree(Node **root, int *errorCode) {
    if (root == nullptr || *root == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    freeNodes(*root, errorCode);
    *root = nullptr;
}