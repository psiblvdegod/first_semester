#include "tree.h"
#include <stdlib.h>

typedef struct Node {
    Value value;
    struct Node * leftChild;
    struct Node * rightChild;
} Node;

typedef struct Tree {
    Node * root;
} Tree;

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

void addChild(Node * parent, Node * child, Position position, bool * errorCode) {
    if (parent == NULL || child == NULL) {
        *errorCode = true;
        return;
    }
    if (position == left) {
        parent->leftChild = child;
    }
    else {
        parent->rightChild = child;
    }
}

Node * getRoot(Tree * tree) {
    if (tree == NULL) {
        return NULL;
    }
    return tree->root;
}

Node * getChild(Node * parent, Position position, bool * errorCode) {
    if (parent == NULL) {
        return NULL;
    }
    if (position == left) {
        return parent->leftChild;
    }
    else {
        return parent->rightChild;
    }
}

Tree * createTree(Node * root, bool * errorCode) {
    Tree * tree = calloc(1, sizeof(Tree));
    if (tree == NULL) {
        *errorCode = true;
        return NULL;
    }
    tree->root = root;
    return tree;
}

Value getValue(Node * node, bool * errorCode) {
    if (node == NULL) {
        *errorCode = true;
        return '\0';
    }
    return node->value;
}