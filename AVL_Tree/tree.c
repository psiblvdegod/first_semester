#include "AVL_Tree.h"
#include "errorCode.h"
#include "tree.h"

void insertIntoTree(Node **root, Value value, Key key, int *errorCode) {
    if (root == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    if (value == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    if (key == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    Node *newNode = createNode(value, key, errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    bool isHeightChanged = false;
    *root = insertIntoAVLTree(*root, newNode, &isHeightChanged);
}

void deleteFromTree(Node **root, Key key, int *errorCode) {
    if (root == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    if (key == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    bool isHeightChanged = false;
    *root = deleteFromAVLTree(*root, key, &isHeightChanged);
}

Value searchInTree(Node *node, Key key, int *errorCode) {
    if (key == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return nullptr;
    }
    return searchInAVLTree(node, key);
}

void deleteTree(Node **root, int *errorCode) {
    if (root == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    deleteAVLTree(*root, errorCode);
}