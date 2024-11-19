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

//child's position for addChild() and getChild()
typedef enum {
    left,
    right
} Position;

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

Node * getChild(Node * parent, Position position) {
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

Tree * createTree(Node * root, bool * errorCode) {
    Tree * tree = calloc(1, sizeof(Tree));
    if (tree == NULL) {
        *errorCode = true;
        return NULL;
    }
    tree->root = root;
    return tree;
}

Node * getRoot(Tree * tree) {
    if (tree == NULL) {
        return NULL;
    }
    return tree->root;
}

Node * getNodeByKey(Tree * tree, int key, bool * errorCode) {
    if (tree == NULL) {
        return NULL;
    }
    Node * currentNode = getRoot(tree);
    while (currentNode != NULL && getKey(currentNode, errorCode) != key) {
        currentNode = getChild(currentNode, key < getKey(currentNode, errorCode) ? left : right);
    }
    return currentNode;
}

Node * findSuitablePosition(Tree * tree, int key, bool * errorCode) {
    if (tree == NULL) {
        return NULL;
    }
    Node * result = getRoot(tree);
    Node * currentNode =  getRoot(tree);
    while (currentNode != NULL) {
        currentNode = getChild(currentNode, key < getKey(currentNode, errorCode) ? left : right);
        if (currentNode != NULL) {
            result = currentNode;
        }
    }
    return result;
}

Node * getParentByNode(Tree * tree, Node * node, bool * errorCode) {
    int key = getKey(node, errorCode);
    Node * currentNode = getRoot(tree);
    while (currentNode != NULL && getChild(currentNode, left) != node && getChild(currentNode, right) != node) {
        if (key < getKey(currentNode, errorCode)) {
            currentNode = getChild(currentNode, left);
        }
        else {
            currentNode = getChild(currentNode, right);
        }
    }
    return currentNode;
}

void addNode(Tree * tree, Node * newNode, bool * errorCode) {
    if (tree == NULL || newNode == NULL) {
        return;
    }
    int newNodeKey = getKey(newNode, errorCode);
    Node * position = findSuitablePosition(tree, newNodeKey, errorCode);
    int positionKey = getKey(position, errorCode);
    if (newNodeKey < positionKey) {
        addChild(position, newNode, left, errorCode);
    }
    else if (newNodeKey > positionKey) {
        addChild(position, newNode, right, errorCode);
    }
    else if (newNodeKey == positionKey) {
        disposeNode(tree, position, errorCode);
        addNode(tree, newNode, errorCode);
    }
}

void disposeNode(Tree * tree, Node * deletingNode, bool * errorCode) {
    if (getRoot(tree) == deletingNode) {
        if (getChild(deletingNode, left) != NULL) {
            tree->root = getChild(deletingNode, left);
            addNode(tree, getChild(deletingNode, right), errorCode);
        }
        else {
            tree->root = getChild(deletingNode, right);
        }
        free(deletingNode);
        return;
    }
    Node *parent = getParentByNode(tree, deletingNode, errorCode);
    if (parent->leftChild == deletingNode) {
        parent->leftChild = NULL;
    }
    else if (parent->rightChild == deletingNode) {
        parent->rightChild = NULL;
    }
    addNode(tree, getChild(deletingNode, left), errorCode);
    addNode(tree, getChild(deletingNode, right), errorCode);
    free(deletingNode);
}