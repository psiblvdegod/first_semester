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

Node * getValueByKey(Node * currentNode, Value key, char ** result) {
    if (currentNode == NULL) {
        return NULL;
    }
    if (strcmp(key, currentNode->key) < 0) {
        currentNode->leftChild = getValueByKey(currentNode->leftChild, key, result);
    }
    else if (strcmp(key, currentNode->key) > 0) {
        currentNode->rightChild = getValueByKey(currentNode->rightChild, key, result);
    }
    if (strcmp(key, currentNode->key) == 0) {
        *result = currentNode->value;
        return currentNode;
    }
}

Node * doSmallRotation(Node * node, Side direction, bool * flag) {
    *flag = false;
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

Node * doBigRotation(Node * node, Side direction, bool * flag) {
    *flag = false;
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

Node *deleteNode(Node *node, Value key, bool * isHeightChanged) {
    bool externalFlagForInsert = false;
    if (strcmp(key, node->key) < 0) {
        node->leftChild = deleteNode(node->leftChild, key, isHeightChanged);
    }
    else if (strcmp(key, node->key) > 0){
        node->rightChild = deleteNode(node->rightChild, key, isHeightChanged);
    }
    if (strcmp(key, node->key) == 0) {
        if (node->leftChild == NULL && node->rightChild == NULL) {
            free(node);
            return NULL;
        }
        else if (node->leftChild != NULL && node->rightChild != NULL) {
            Node * children = insert(node->leftChild, node->rightChild, isHeightChanged);
            free(node);
            return children;
        }
        else if (node->leftChild != NULL) {
            Node * child = node->leftChild;
            free(node);
            return child;
        }
        else if (node->rightChild != NULL) {
            Node * child = node->rightChild;
            free(node);
            return child;
        }
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

