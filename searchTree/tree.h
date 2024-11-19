#pragma once
#include <stdbool.h>

typedef struct Node Node;

typedef char * Value;

typedef struct Tree Tree;

Node * createNode(Value value, int key, bool * errorCode);

Value getValue(Node * node, bool * errorCode);

int getKey(Node * node, bool * errorCode);

//stores root. first create root using createNode(), then createTree(<root>)
Tree * createTree(Node * root, bool * errorCode);

Node * getRoot(Tree * tree);

//if there is a node in the tree with such key, returns this node.
//else returns a node that can become a parent of the node with such key.
//does not report which of the cases happened,
//so requires comparing the keys after call.
Node * getNodeByKey(Tree * tree, int key, bool * errorCode);

Node * getParentByNode(Tree * tree, Node * node, bool * errorCode);

void addNode(Tree * tree, Node * newNode, bool * errorCode);

void disposeNode(Tree * tree, Node * deletingNode, bool * errorCode);

Node * findSuitablePosition(Tree * tree, int key, bool * errorCode);


