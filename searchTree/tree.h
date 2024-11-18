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

Node * getChild(Node * parent, Position position, bool * errorCode);

Value getValue(Node * node, bool * errorCode);

//stores root as struct Tree. first create node, witch will be the root, then createTree(<root>)
Tree * createTree(Node * root, bool * errorCode);

Node * getRoot(Tree * tree);

void addNode(Tree * tree, Node * newNode, bool * errorCode);

//calls addNode to deletingNode's children.
void disposeNode(Tree * tree, Node * deletingNode, bool * errorCode);

//if there is a node with such key, returns this node.
//else returns a node that can become a parent of the node with such key.
//does not report which of the cases happened,
//so requires comparing the keys after call.
Node * getNodeByKey(Tree * tree, int key, bool * errorCode);

int getKey(Node * node, bool * errorCode);