#pragma once

#include "typeDefinitions.h"

Node *createNode(Value value, Key key, int *errorCode);

Node *insertIntoAVLTree(Node *node, Node *newNode, bool *isHeightChanged);

Node *deleteFromAVLTree(Node *node, Key key, bool *isHeightChanged);

Value searchInAVLTree(Node *node, Key key);

void deleteAVLTree(Node *root);