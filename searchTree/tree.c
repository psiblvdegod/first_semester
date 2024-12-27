#include "tree.h"
#include "errorCode.h"
#include <string.h>
#include <stdlib.h>

typedef struct Node {
    Value value;
    Key key;
    struct Node *leftChild;
    struct Node *rightChild;
} Node;

Node *createNode(Value value, Key key, int *errorCode) {
    Node *node = calloc(1, sizeof(Node));
    if (node == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }
    node->key = key;
    node->value = value;
    node->leftChild = NULL;
    node->rightChild = NULL;
    return node;
}

Node *insertRecursive(Node *node, Node *newNode, int *errorCode) {
    if (newNode == NULL) {
        return node;
    }
    if (node == NULL) {
        return newNode;
    }
    if (newNode->key < node->key) {
        node->leftChild = insertRecursive(node->leftChild, newNode, errorCode);
    }
    else if (newNode->key > node->key) {
        node->rightChild = insertRecursive(node->rightChild, newNode, errorCode);
    }
    else {
        node->value = newNode->value;
        free(newNode);
    }
    return node;
}

Node *insert(Node *root, Value value, Key key, int *errorCode) {
    return insertRecursive(root, createNode(value, key, errorCode), errorCode);
}

Node *disposeRecursive(Node *node, Key key, int *errorCode) {
    if (node == NULL) {
        return node;
    }
    if (key < node->key) {
        node->leftChild = disposeRecursive(node->leftChild, key, errorCode);
    }
    else if (key > node->key) {
        node->rightChild = disposeRecursive(node->rightChild, key, errorCode);
    }
    else {
        Node *children = insertRecursive(node->leftChild, node->rightChild, errorCode);
        free(node);
        return children;
    }
    return node;
}

Node *dispose(Node *node, Key key, int *errorCode) {
    if (node == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return NULL;
    }
    return disposeRecursive(node, key, errorCode);
}

Value search(Node *node, Key key) {
    while (node != NULL) {
        if (key < node->key) {
            node = node->leftChild;
        }
        else if (key > node->key) {
            node = node->rightChild;
        }
        else {
            return node->value;
        }
    }
    return NULL;
}

void freeNodes(Node *node, int *errorCode) {
    if (node == NULL) {
        return;
    }
    freeNodes(node->leftChild, errorCode);
    freeNodes(node->rightChild, errorCode);
    free(node);
}

void deleteTree(Node **root, int *errorCode) {
    if (root == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    freeNodes(*root, errorCode);
    *root = NULL;
}