#pragma once

#include <stdbool.h>

#define WORD_MAX_SIZE 50

typedef struct Node Node;

typedef char *Value;

typedef int Key;

// creates node
Node *createNode(Value value, Key key, int *errorCode);

// adds new node to tree preserving binary search tree properties.
Node *insertInTree(Node *root, Value value, Key key, int *errorCode);

// deletes node by key preserving binary search tree properties.
Node *deleteFromTree(Node *root, Key key, bool *wasDeletionSuccessful, int *errorCode);

// searches value by key
Value searchInTree(Node *root, Key key);

// frees allocated memory, turns pointer NULL
void deleteTree(Node **root, int *errorCode);

// if tree satisfies binary search tree properties, returns true.
// else returns false.
bool verifyBinarySearchTreeInvariant(Node *root);