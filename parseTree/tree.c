#include "tree.h"
#include "errorCode.h"
#include <stdlib.h>

typedef struct Node {
    Value value;
    struct Node *leftChild;
    struct Node *rightChild;
} Node;

Node * createNode(Value value, int *errorCode) {
    Node * node = calloc(1, sizeof(Node));
    if (node == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }
    node->value = value;
    node->leftChild = NULL;
    node->rightChild = NULL;
    return node;
}

void addChild(Node *parent, Node *child, Position position, int *errorCode) {
    if (parent == NULL || child == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    if (position == left) {
        parent->leftChild = child;
    }
    else if (position == right){
        parent->rightChild = child;
    }
}

Node *getChild(Node *parent, Position position, int *errorCode) {
    if (parent == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return NULL;
    }
    if (position == left) {
        return parent->leftChild;
    }
    else if (position == right) {
        return parent->rightChild;
    }
}

Value getValue(Node *node, int *errorCode) {
    if (node == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return '\0';
    }
    return node->value;
}

void freeNodes(Node *node, int *errorCode) {
    if (node == NULL) {
        return;
    }
    freeNodes(getChild(node, left, errorCode), errorCode);
    freeNodes(getChild(node, right, errorCode), errorCode);
    free(node);
}

void deleteTree(Node **root, int *errorCode) {
    if (root == NULL || *root == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    freeNodes(*root, errorCode);
    *root = NULL;
}