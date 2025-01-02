#pragma once
#include <stdbool.h>

typedef struct Node Node;

typedef int Value;

// child's position for addChild() and getChild()
typedef enum {
    left,
    right
} Position;

// creates node
Node *createNode(Value value, int *errorCode);

// ties two nodes adding left/right child, depends on position, to parent
void addChild(Node *parent, Node *child, Position position, int *errorCode);

// returns left/right child, depends on position
Node *getChild(Node *parent, Position position, int *errorCode);

// returns node's value
Value getValue(Node *node, int *errorCode);

// frees allocated memory, turns pointer NULL
void deleteTree(Node **root, int *errorCode);