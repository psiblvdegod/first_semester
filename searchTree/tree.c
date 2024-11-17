#include "tree.h"
#include <stdlib.h>

typedef struct Node {
    int key;
    Value value;
    struct Node * leftChild;
    struct Node * rightChild;
} Node;

typedef struct Tree {
    Node * root;
} Tree;

Node * createNode(Value value, int key, bool * errorCode) {
    Node * node = calloc(1, sizeof(Node));
    if (node == NULL) {
        *errorCode = true;
        return NULL;
    }
    node->value = value;
    node->key = key;
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
        return NULL;
    }
    return node->value;
}

int getKey(Node * node, bool * errorCode) {
    if (node == NULL) {
        *errorCode = true;
        return -1;
    }
    return node->key;
}

Node * getNodeByKey(Node * currentNode, int key, bool * errorCode) {
    Node * child = NULL;
    if (key < getKey(currentNode, errorCode)) {
        child = getChild(currentNode, left, errorCode);
    }
    else {
        child = getChild(currentNode, right, errorCode);
    }
    if (child == NULL) {
        return currentNode;
    }
    getNodeByKey(child, key, errorCode);
}

void disposeNode(Tree * tree, Node * deletingNode, bool * errorCode) {
    int deletingNodeKey = getKey(deletingNode, errorCode);
    Node * parent = getNodeByKey(getRoot(tree), deletingNodeKey, errorCode);
    if (parent != NULL) {
        if (parent->leftChild == deletingNode) {
            parent->leftChild = NULL;
        }
        if (parent->rightChild == deletingNode) {
            parent->rightChild = NULL;
        }
    }
    addNode(tree, getChild(deletingNode, left, errorCode), errorCode);
    addNode(tree, getChild(deletingNode, right, errorCode), errorCode);
    free(deletingNode);
}

void addNode(Tree * tree, Node * newNode, bool * errorCode) {
    if (tree == NULL || newNode == NULL) {
        return;
    }
    int newNodeKey = getKey(newNode, errorCode);
    Node * root = getRoot(tree);
    Node * position = getNodeByKey(root, newNodeKey, errorCode);
    int positionKey = getKey(position, errorCode);
    if (newNodeKey < positionKey) {
        addChild(position, newNode, left, errorCode);
    }
    if (newNodeKey > positionKey) {
        addChild(position, newNode, right, errorCode);
    }
    if (newNodeKey == positionKey) {
        disposeNode(tree, position, errorCode);
        addNode(tree, newNode, errorCode);
    }
}