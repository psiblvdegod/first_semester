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
    if (strcmp(key, node->key) == 0) {
        if (node->leftChild == NULL && node->rightChild == NULL) { //лист
            free(node);
            return NULL;
        }
        else if (node->leftChild != NULL && node->rightChild != NULL) { //оба есть
            if (node->balance <= 0) {
                Node * children = insert(node->leftChild, node->rightChild, &externalFlagForInsert);
                free(node);
                return children;
            }
            else {
                Node * children = insert(node->rightChild, node->leftChild, &externalFlagForInsert);
                free(node);
                return children;
            }
        }
        else if (node->leftChild != NULL) { //левый
            Node * child = node->leftChild;
            free(node);
            return child;
        }
        else if (node->rightChild != NULL) {// правый
            Node * child = node->rightChild;
            free(node);
            return child;
        }
    }
    else if (strcmp(key, node->key) < 0) {
        node->leftChild = deleteNode(node->leftChild, key, isHeightChanged);
    }
    else {
        node->rightChild = deleteNode(node->rightChild, key, isHeightChanged);
    }
    return node;
    //return balance(node, errorCode);
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
        *flag = false; //ничего не делает
        return newNode;
    }
    if (strcmp(newNode->key, currentNode->key) < 0) {
        currentNode->leftChild = insert(currentNode->leftChild, newNode, flag);
        if (*flag || currentNode->leftChild == newNode) {
            ++currentNode->balance;
            //*flag = currentNode->balance != 0;   // одно из двух
            if (currentNode->balance == 0) {       // idk
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
            //*flag = currentNode->balance != 0;
            if (currentNode->rightChild == newNode) {
                *flag = currentNode->leftChild == NULL;
            }
            if (currentNode->balance == 0) {
                *flag = false;
            }
        }
    }
    //return currentNode;
    return balance(currentNode, flag);
}


/*
bool addNode(Node* node, const char* key, const char* value, bool* errorCode) {
    if (strcmp(key, node->value.key) == 0) {
        node->value.value = value;
        return false;
    }

    if (node->left == NULL && strcmp(key, node->value.key) < 0) {
        Node* newNode = createTree(key, value, errorCode);
        node->left = newNode;
        --node->balance;
        return node->balance != 0;
    }
    else if (node->right == NULL && strcmp(key, node->value.key) > 0) {
        Node* newNode = createTree(key, value, errorCode);
        node->right = newNode;
        ++node->balance;
        return node->balance != 0;
    }

    bool needChangeBalance = false;
    if (strcmp(key, node->value.key) > 0) {
        needChangeBalance = addNode(node->right, key, value, errorCode);
        if (needChangeBalance) {
            ++node->balance;
            return node->balance != 0;
        }
        return false;
    }
    if (strcmp(key, node->value.key) < 0) {
        needChangeBalance = addNode(node->left, key, value, errorCode);
        if (needChangeBalance) {
            --node->balance;
            return node->balance != 0;
        }
        return false;
    }
}

 */

