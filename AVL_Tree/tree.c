#include "tree.h"
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    Value key;
    Value value;
    int balance;
    struct Node *leftChild;
    struct Node *rightChild;
} Node;

// defines rotation direction
typedef enum {
    left,
    right
} Direction;

Node *createNode(Value value, Value key, int *errorCode) {
    Node *node = calloc(1, sizeof(Node));
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

Value search(Node *node, Value key) {
    if (node == NULL) {
        return NULL;
    }
    while (node != NULL) {
        if (strcmp(key, node->key) < 0) {
            node = node->leftChild;
        }
        else if (strcmp(key, node->key) > 0) {
            node = node->rightChild;
        }
        else if (strcmp(key, node->key) == 0) {
            break;
        }
    }
    if (node == NULL) {
        return NULL;
    }
    return node->value;
}

Node * doSmallRotation(Node * node, Direction direction) {
    //*flag = false;
    if (direction == left) {
        Node *nodeRightChild = node->rightChild;
        if (nodeRightChild != NULL) {
            node->rightChild = nodeRightChild->leftChild;
            nodeRightChild->leftChild = node;
            return nodeRightChild;
        }
    }
    if (direction == right) {
        Node *nodeLeftChild = node->leftChild;
        if (nodeLeftChild != NULL) {
            node->leftChild = nodeLeftChild->rightChild;
            nodeLeftChild->rightChild = node;
            return nodeLeftChild;
        }
    }
}

Node * doBigRotation(Node * node, Direction direction) {
    //*flag = false;
    if (direction == left) {
        Node *centralDescendant = node->rightChild->leftChild;
        node->rightChild->leftChild = centralDescendant->rightChild;
        centralDescendant->rightChild = node->rightChild;
        node->rightChild = centralDescendant->leftChild;
        centralDescendant->leftChild = node;
        return centralDescendant;
    }
    if (direction == right) {
        Node *centralDescendant = node->leftChild->rightChild;
        node->leftChild->rightChild = centralDescendant->leftChild;
        centralDescendant->leftChild = node->leftChild;
        node->leftChild = centralDescendant->rightChild;
        centralDescendant->rightChild = node;
        return centralDescendant;
    }
}

Node *balance(Node * node, bool *isHeightChanged) {
    if (node->balance == -2) {
        if (node->rightChild->balance <= 0) {
            node = doSmallRotation(node, left);
            if (node->balance == -1) {
                node->balance = 0;
                node->leftChild->balance = 0;
            }
            else if (node->balance == 0) {
                node->balance = 1;
                node->leftChild->balance = -1;
            }
        }
        else {
            node = doBigRotation(node, left);
            if (node->balance == 1) {
                node->leftChild->balance = 0;
                node->rightChild->balance = -1;
            } else if (node->balance == -1) {
                node->leftChild->balance = 1;
                node->rightChild->balance = 0;
            } else if (node->balance == 0) {
                node->leftChild->balance = 0;
                node->rightChild->balance = 0;
            }
            node->balance = 0;
        }
    }
    if (node->balance == 2) {
        if (node->leftChild->balance >= 0) {
            node = doSmallRotation(node, right);
            if (node->balance == 1) {
                node->balance = 0;
                node->rightChild->balance = 0;
            }
            else if (node->balance == 0) {
                node->balance = 1;
                node->rightChild->balance = -1;
            }
        }
        else {
            node = doBigRotation(node, right);
            if (node->balance == 1) {
                node->leftChild->balance = 0;
                node->rightChild->balance = -1;
            } else if (node->balance == -1) {
                node->leftChild->balance = 1;
                node->rightChild->balance = 0;
            } else if (node->balance == 0) {
                node->leftChild->balance = 0;
                node->rightChild->balance = 0;
            }
            node->balance = 0;
        }
    }
    if (node->balance == 0) {
        *isHeightChanged = false;
    }
    return node;
}

Node *insert(Node *node, Node *newNode, bool *isHeightChanged) {
    if (newNode == NULL) {
        *isHeightChanged = false;
        return node;
    }
    if (node == NULL) {
        *isHeightChanged = true;
        return newNode;
    }
    if (strcmp(newNode->key, node->key) == 0) {
        node->value = newNode->value;
        free(newNode);
        *isHeightChanged = false;
    }
    else if (strcmp(newNode->key, node->key) < 0) {
        node->leftChild = insert(node->leftChild, newNode, isHeightChanged);
        if (*isHeightChanged) {
            ++node->balance;
        }
    }
    else if (strcmp(newNode->key, node->key) > 0) {
        node->rightChild = insert(node->rightChild, newNode, isHeightChanged);
        if (*isHeightChanged) {
            --node->balance;
        }
    }
    return balance(node, isHeightChanged);
}

Node *findClosest(Node *current, Node *new) {
    if (current->leftChild == NULL) {
        current->key = new->key;
        current->value = new->value;
        free(new);
        return NULL;
    }
    current->leftChild = findClosest(current->leftChild, new);
    return current;
}

Node *dispose(Node *node, Value key, bool *isHeightChanged) {
    if (node == NULL) {
        *isHeightChanged = false;
        return NULL;
    }
    if (strcmp(key, node->key) < 0) {
        node->leftChild = dispose(node->leftChild, key, isHeightChanged);
        if (*isHeightChanged) {
            --node->balance;
        }
    }
    else if (strcmp(key, node->key) > 0) {
        node->rightChild = dispose(node->rightChild, key, isHeightChanged);
        if (*isHeightChanged) {
            ++node->balance;
        }
    }
    else if (strcmp(key, node->key) == 0) {
        *isHeightChanged = true;
        if (node->rightChild == NULL && node->leftChild == NULL) {
            free(node);
            return NULL;
        }
        else if (node->rightChild == NULL) {
            Node *child = node->leftChild;
            free(node);
            return child;
        }
        else if (node->leftChild == NULL) {
            Node *child = node->rightChild;
            free(node);
            return child;
        }
        else {
            Node *closestNode = findClosest(node, node);
            node->key = closestNode->key;
            node->value = closestNode->value;
            return node;
        }
    }
    return balance(node, isHeightChanged);
}