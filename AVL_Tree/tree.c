#include "errorCode.h"
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
    if (node == nullptr) {
        *errorCode = true;
        return nullptr;
    }
    node->value = strdup(value);
    if (node->value == nullptr) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        free(node);
        return nullptr;
    }
    node->key = strdup(key);
    if (node->key == nullptr) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        free(node->key);
        free(node);
        return nullptr;
    }
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

Node *doSmallRotation(Node *node, Direction direction) {
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

Node *doBigRotation(Node *node, Direction direction) {
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

Node *balance(Node * node) {
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
    node = balance(node);
    if (node->balance == 0) {
        *isHeightChanged = false;
    }
    return node;
}

Node *dispose(Node *node, Value key, bool *isHeightChanged) {
    if (node == nullptr) {
        *isHeightChanged = false;
        return nullptr;
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
        if (node->rightChild == nullptr && node->leftChild == nullptr) {
            free(node->key);
            free(node->value);
            free(node);
            return nullptr;
        }
        else if (node->rightChild == nullptr) {
            Node *child = node->leftChild;
            free(node->key);
            free(node->value);
            free(node);
            return child;
        }
        else if (node->leftChild == nullptr) {
            Node *child = node->rightChild;
            free(node->key);
            free(node->value);
            free(node);
            return child;
        }
        else {
            Node *closest = node->rightChild;
            while (closest->leftChild != nullptr) {
                closest = closest->leftChild;
            }
            Value temp1 = node->value;
            Value temp2 = node->key;
            node->value = closest->value;
            node->key = closest->key;
            closest->value = temp1;
            closest->key = temp2;
            node->rightChild = dispose(node->rightChild, key, isHeightChanged);
            if (*isHeightChanged) {
                ++node->balance;
            }
        }
    }
    node = balance(node);
    if (node->balance == -1 || node->balance == 1) {
        *isHeightChanged = false;
    }
    return node;
}

