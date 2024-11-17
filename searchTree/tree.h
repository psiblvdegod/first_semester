#pragma once
#include <stdbool.h>

typedef struct Node Node;

typedef char * Value;

typedef struct Tree Tree;

//child's position for addChild() and getChild()
typedef enum {
    left,
    right
} Position;

Node * createNode(Value value, int key, bool * errorCode);

void addChild(Node * parent, Node * child, Position position, bool * errorCode);

Node * getChild(Node * parent, Position position, bool * errorCode);

Value getValue(Node * node, bool * errorCode);

//stores root. first create node, witch will be the root, then createTree(<root>)
Tree * createTree(Node * root, bool * errorCode);

Node * getRoot(Tree * tree);

void addNode(Tree * tree, Node * newNode, bool * errorCode);

void disposeNode(Tree * tree, Node * deletingNode, bool * errorCode);

Node * getNodeByKey(Node * currentNode, int key, bool * errorCode);

int getKey(Node * node, bool * errorCode);