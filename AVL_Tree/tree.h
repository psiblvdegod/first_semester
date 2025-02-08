#pragma once

#include "typeDefinitions.h"
#include <stdbool.h>

// adds element with required value and key to tree
void insertIntoTree(Node **root, Value value, Key key, int *errorCode);

// if there is element with such key in the tree returns it`s value
// else returns nullptr
Value searchInTree(Node *node, Key key, int *errorCode);

// deletes element from tree
void deleteFromTree(Node **root, Key key, int *errorCode);

// frees allocated memory turns pointer NULL
void deleteTree(Node **root, int *errorCode);