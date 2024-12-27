#pragma once
#include <stdbool.h>

typedef struct Node Node;

typedef char *Value;

typedef int Key;

// child's position for addChild() and getChild()
typedef enum {
    left,
    right
} Position;

// creates node
Node *createNode(Value value, Key key, int *errorCode);

// adds new node to tree preserving binary search tree properties.
Node *insert(Node *root, Value value, Key key, int *errorCode);

// deletes node by key preserving binary search tree properties.
Node *dispose(Node *root, Key key, int *errorCode);

// searches value by key
Value search(Node *node, Key key);

// frees allocated memory, turns pointer NULL
void deleteTree(Node **root, int *errorCode);