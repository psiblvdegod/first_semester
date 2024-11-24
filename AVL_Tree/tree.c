#include "tree.h"
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    Value key;
    Value value;
    int balance;
    struct Node * leftChild;
    struct Node * rightChild;
} Node;

Node * createNode(Value value, Value key, bool * errorCode) {
    Node * node = calloc(1, sizeof(Node));
    if (node == NULL) {
        *errorCode = true;
        return NULL;
    }
    node->value = value;
    node->key = key;
    node->balance = 0;
    node->leftChild = NULL;
    node->rightChild = NULL;
    return node;
}

Node * getChild(Node * parent, Side position) {
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

Value getKey(Node * node, bool * errorCode) {
    if (node == NULL) {
        *errorCode = true;
        return "0";
    }
    return node->key;
}

Node * getNodeByKey(Node * currentNode, Value key, bool * errorCode) {
    while (currentNode != NULL) {
        if (strcmp(key, currentNode->key) < 0) {
            currentNode = currentNode->leftChild;
        }
        else {
            currentNode = currentNode->rightChild;
        }
        if (currentNode->key == key) {
            return currentNode;
        }
    }
}

Node * doSmallRotation(Node * node, Side direction, bool * errorCode) {
    if (node == NULL) {
        *errorCode = true;
        return NULL;
    }
    if (direction == left) {
        Node * nodeRightChild = node->rightChild;
        if (nodeRightChild != NULL) {
            node->rightChild = nodeRightChild->leftChild;
            nodeRightChild->leftChild = node;
            return nodeRightChild;
        }
    }

    if (direction == right) {
        Node * nodeLeftChild = node->leftChild;
        if (nodeLeftChild != NULL) {
            node->leftChild = nodeLeftChild->rightChild;
            nodeLeftChild->rightChild = node;
            return nodeLeftChild;
        }
    }
}

Node * doBigRotation(Node * node, Side direction, bool * errorCode) {
    if (node == NULL) {
        *errorCode = true;
        return NULL;
    }
    if (direction == left) {
        Node * rightLeftDescendant = node->rightChild->leftChild;
        doSmallRotation(node->rightChild, right, errorCode);
        node->rightChild = rightLeftDescendant;
        doSmallRotation(node, left, errorCode);
        return rightLeftDescendant;
    }
    if (direction == right) {
        Node * leftRightDescendant = node->leftChild->rightChild;
        doSmallRotation(node->leftChild, left, errorCode);
        node->leftChild = leftRightDescendant;
        doSmallRotation(node, right, errorCode);
        return leftRightDescendant;
    }
}

Node * balance(Node * node, bool * errorCode) {
    if (node->balance >= 2) {
        if (node->rightChild->balance >= 0) {
            return doSmallRotation(node, left, errorCode);
        }
        return doBigRotation(node, left, errorCode);
    }
    if (node->balance <= -2) {
        if (node->leftChild->balance <= 0) {
            return doSmallRotation(node, right, errorCode);
        }
        return doBigRotation(node, right, errorCode);
    }
    return node;
}

Node * insert (Node * currentNode, Node * newNode, bool * errorCode) {
    if (newNode == NULL) {
        return NULL;
    }
    if (currentNode == NULL) {
        return newNode;
    }
    if (strcmp(newNode->key, currentNode->key) == 0) {
        newNode->leftChild = currentNode->leftChild;
        newNode->rightChild = currentNode->rightChild;
        free(currentNode);
        return newNode;
    }
    if (strcmp(newNode->key, currentNode->key) < 0) {
        currentNode->leftChild = insert(currentNode->leftChild, newNode, errorCode);
        --currentNode->balance;
    }
    if (strcmp(newNode->key, currentNode->key) > 0) {
        currentNode->rightChild = insert(currentNode->rightChild, newNode, errorCode);
        ++currentNode->balance;
    }
    return currentNode;
    return balance(currentNode, errorCode);
}

Node *deleteNode(Node *node, Value key, bool * errorCode) {
    if (node == NULL) {
        *errorCode = true;
        return NULL;
    }
    if (strcmp(key, node->key) == 0) {
        if (node->leftChild == NULL && node->rightChild == NULL) { //лист
            free(node);
            return NULL;
        }
        else if (node->leftChild != NULL) { //есть левый и правый или только левый
            insert(node->leftChild, node->rightChild, errorCode);
            return node->leftChild; //надо как-то освободить память (для целой ветви)
        }
        else if (node->rightChild != NULL) { //есть только правый
            return node->rightChild; //надо как-то освободить память (только удаленный узел)
        }
    }
    if (strcmp(key, node->key) < 0) {
        node->leftChild = deleteNode(node->leftChild, key, errorCode);
        if (!errorCode) {
            ++node->leftChild->balance;
        }
    }
    else {
        node->rightChild = deleteNode(node->rightChild, key, errorCode);
        if (!errorCode) {
            --node->leftChild->balance;
        }
    }
    return node;
    return balance(node, errorCode);
}







/*
Node * insert(Node ** currentNode, Node * newNode, bool * errorCode) {
    if (newNode == NULL) {
        return NULL;
    }
    if (*currentNode == NULL) {
        *currentNode = newNode;
        return NULL;
    }
    if (strcmp(newNode->key, (*currentNode)->key) < 0) {
        insert(&((*currentNode)->leftChild), newNode, errorCode);
        --(*currentNode)->balance;
    }
    else if (strcmp(newNode->key, (*currentNode)->key) > 0) {
        insert(&((*currentNode)->rightChild), newNode, errorCode);
        ++(*currentNode)->balance;
    }
    return *currentNode;
    //return balance(*currentNode, errorCode);
}
*/