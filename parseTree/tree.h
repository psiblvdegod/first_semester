#pragma once
#include <stdbool.h>

typedef struct Node Node;

typedef int Value;

typedef struct Tree {
    Node * root;
} Tree;

typedef enum {
    left,
    right
} Position;

Node * createNode(Value value, bool * errorCode);

void addChild(Node * parent, Node * child, Position position, bool * errorCode);

Node * getRoot(Tree * tree);

Node * getChild(Node * parent, Position position, bool * errorCode);

Value getValue(Node * node, bool * errorCode);

Tree * createTree(Node * root, bool * errorCode);