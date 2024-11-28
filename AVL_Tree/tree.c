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

//defines rotation direction
typedef enum { left, right } Direction;

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

Value findValueByKey(Node * node, Value key) {
    if (node == NULL) {
        return NULL;
        //*errorCode = true;
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

Node * doSmallRotation(Node * node, Direction direction, bool * flag) {
    //*flag = false;
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

Node * doBigRotation(Node * node, Direction direction, bool * flag) {
    //*flag = false;
    if (direction == left) {
        Node * centralDescendant = node->rightChild->leftChild;
        node->rightChild->leftChild = centralDescendant->rightChild;
        centralDescendant->rightChild = node->rightChild;
        node->rightChild = centralDescendant->leftChild;
        centralDescendant->leftChild = node;
        return centralDescendant;
    }
    if (direction == right) {
        Node * centralDescendant = node->leftChild->rightChild;
        node->leftChild->rightChild = centralDescendant->leftChild;
        centralDescendant->leftChild = node->leftChild;
        node->leftChild = centralDescendant->rightChild;
        centralDescendant->rightChild = node;
        return centralDescendant;
    }
}

Node * balance(Node * node, bool * flag) {
    if (node->balance == -2) {
        if (node->rightChild->balance <= 0) {
            node = doSmallRotation(node, left, flag);
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
            node = doBigRotation(node, left, flag);

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
            node = doSmallRotation(node, right, flag);
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
            node = doBigRotation(node, right, flag);

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
        *flag = false;
    }
    return node;
}

Node *dispose(Node *node, Value key, bool * isHeightChanged) {
    if (node == NULL) {
        return NULL;
    }
    if (strcmp(key, node->key) < 0) {
        node->leftChild = dispose(node->leftChild, key, isHeightChanged);
        if (*isHeightChanged) {
            --node->balance;
            if (node->balance == 1 || node->balance == -1) {
                *isHeightChanged = false;
            }
        }
    }
    else if (strcmp(key, node->key) > 0){
        node->rightChild = dispose(node->rightChild, key, isHeightChanged);
        if (*isHeightChanged) {
            ++node->balance;
            if (node->balance == 1 || node->balance == -1) {
                *isHeightChanged = false;
            }
        }
    }
    if (strcmp(key, node->key) == 0) {
        if (node->leftChild == NULL && node->rightChild == NULL) {
            //free(node);
            return NULL;
        }
        else if (node->leftChild != NULL && node->rightChild != NULL) {
            Node * children = insert(node->leftChild, node->rightChild, isHeightChanged);
            //free(node);
            return children;
        }
        else if (node->leftChild != NULL) {
            Node * child = node->leftChild;
            //free(node);
            return child;
        }
        else if (node->rightChild != NULL) {
            Node * child = node->rightChild;
            //free(node);
            return child;
        }
        *isHeightChanged = true;
    }
    return balance(node, isHeightChanged);
}

Node * insert (Node * currentNode, Node * newNode, bool * flag) {
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
        *flag = false;
        return newNode;
    }
    if (strcmp(newNode->key, currentNode->key) < 0) {
        currentNode->leftChild = insert(currentNode->leftChild, newNode, flag);
        if (*flag || currentNode->leftChild == newNode) {
            ++currentNode->balance;
            if (currentNode->balance == 0) {
                *flag = false;
            }
            if (currentNode->leftChild == newNode) {
                *flag = currentNode->rightChild == NULL;
            }
        }
    }
    if (strcmp(newNode->key, currentNode->key) > 0) {
        currentNode->rightChild = insert(currentNode->rightChild, newNode, flag);
        if (*flag || currentNode->rightChild == newNode) {
            --currentNode->balance;
            if (currentNode->rightChild == newNode) {
                *flag = currentNode->leftChild == NULL;
            }
            if (currentNode->balance == 0) {
                *flag = false;
            }
        }
    }
    return balance(currentNode, flag);
}

