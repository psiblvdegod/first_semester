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

//if there isn't node with such key, returns NULL
Node * getNodeByKey(Tree * tree, int key, bool * errorCode);

Node * getParentByNode(Tree * tree, Node * node, bool * errorCode);

void addNode(Tree * tree, Node * newNode, bool * errorCode);

void disposeNode(Tree * tree, Node * deletingNode, bool * errorCode);

//finds suitable parent for new node using it's key.
//if tree is empty (==NULL) returns NULL
Node * findSuitablePosition(Tree * tree, int key, bool * errorCode);


