#pragma once

#include "typeDefinitions.h"

// creates node with required value and key
Node *createNode(Value value, Key key, int *errorCode);

// adds element to AVL tree preserving it`s properties
Node *insertIntoAVLTree(Node *node, Node *newNode, bool *isHeightChanged);

// deletes element from AVL tree preserving it`s properties
Node *deleteFromAVLTree(Node *node, Key key, bool *isHeightChanged);

// if there is element with such key in the tree returns it`s value
// else returns nullptr
Value searchInAVLTree(Node *node, Key key);

// if tree satisfies properties of AVL Tree returns true
// else returns false
bool verifyAVLTreeInvariants(Node *root, int *errorCode);

// frees allocated memory and turns pointer NULL
void deleteAVLTree(Node *root, int *errorCode);