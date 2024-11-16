#pragma once
#include <stdbool.h>

typedef struct Node Node;

typedef int Value;

typedef struct Tree Tree;

//child's position for addChild() and getChild()
typedef enum {
    left,
    right
} Position;

Node * createNode(Value value, bool * errorCode);

void addChild(Node * parent, Node * child, Position position, bool * errorCode);

Node * getChild(Node * parent, Position position, bool * errorCode);

Value getValue(Node * node, bool * errorCode);

//stores root. first create node, witch will be the root, then createTree(<root>)
Tree * createTree(Node * root, bool * errorCode);

Node * getRoot(Tree * tree);