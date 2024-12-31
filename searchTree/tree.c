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
    if (node == nullptr) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return nullptr;
    }
    node->key = key;
    node->value = value;
    return node;
}

Node *insertRecursive(Node *node, Node *newNode) {
    if (newNode == nullptr) {
        return node;
        // does not report an error cause newNode may be NULL when called from deleteRecursive()
    }
    if (node == nullptr) {
        return newNode;
    }
    if (newNode->key < node->key) {
        node->leftChild = insertRecursive(node->leftChild, newNode);
    }
    else if (newNode->key > node->key) {
        node->rightChild = insertRecursive(node->rightChild, newNode);
    }
    else {
        node->value = newNode->value;
        free(newNode);
    }
    return node;
}

Node *insertInTree(Node *root, Value value, Key key, int *errorCode) {
    if (value == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return nullptr;
    }
    Node *newNode = createNode(strdup(value), key, errorCode);
    if (*errorCode != NO_ERRORS) {
        return nullptr;
    }
    return insertRecursive(root, newNode);
}

Node *deleteRecursive(Node *node, Key key, bool *wasDeletionSuccessful) {
    if (node == nullptr) {
        *wasDeletionSuccessful = false;
        return node;
    }
    if (key < node->key) {
        node->leftChild = deleteRecursive(node->leftChild, key, wasDeletionSuccessful);
    }
    else if (key > node->key) {
        node->rightChild = deleteRecursive(node->rightChild, key, wasDeletionSuccessful);
    }
    else {
        Node *children = insertRecursive(node->leftChild, node->rightChild);
        free(node->value);
        free(node);
        *wasDeletionSuccessful = true;
        return children;
    }
    return node;
}

Node *deleteFromTree(Node *node, Key key, bool *wasDeletionSuccessful, int *errorCode) {
    if (node == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return nullptr;
    }
    return deleteRecursive(node, key, wasDeletionSuccessful);
}

Value searchInTree(Node *node, Key key) {
    while (node != nullptr) {
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
    return nullptr;
}

void freeNodes(Node *node) {
    if (node == nullptr) {
        return;
    }
    freeNodes(node->leftChild);
    freeNodes(node->rightChild);
    free(node->value);
    free(node);
}

void deleteTree(Node **root, int *errorCode) {
    if (root == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    freeNodes(*root);
    *root = nullptr;
}