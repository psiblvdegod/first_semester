#include "tree.h"
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    Value value;
    struct Node * leftChild;
    struct Node * rightChild;
} Node;

Node * createNode(Value value, bool * errorCode) {
    Node * node = calloc(1, sizeof(Node));
    if (node == NULL) {
        *errorCode = true;
        return NULL;
    }
    node->value = value;
    node->leftChild = NULL;
    node->rightChild = NULL;
    return node;
}

Node * insert (Node * currentNode, Node * newNode) {
    if (newNode == NULL) {
        return NULL;
    }
    if (currentNode == NULL) {
        return newNode;
    }
    if (strcmp(newNode->value, currentNode->value) == 0) {
        newNode->leftChild = currentNode->leftChild;
        newNode->rightChild = currentNode->rightChild;
        free(currentNode);
        return newNode;
    }
    if (strcmp(newNode->value, currentNode->value) < 0) {
        currentNode->leftChild = insert(currentNode->leftChild, newNode);

    }
    if (strcmp(newNode->value, currentNode->value) > 0) {
        currentNode->rightChild = insert(currentNode->rightChild, newNode);
    }
    return currentNode;
}

Node * getChild(Node * node, Side side) {
    if (node == NULL) {
        return NULL;
    }
    if (side == left) {
        return node->leftChild;
    }
    if (side == right) {
        return node->rightChild;
    }
}

Value getValue(Node * node) {
    if (node == NULL) {
        return NULL;
    }
    return node->value;
}