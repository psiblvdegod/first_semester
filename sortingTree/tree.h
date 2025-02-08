#pragma once
#include <stdbool.h>

typedef struct Node Node;

typedef const char * Value;

//child's position for getChild
typedef enum { left, right } Side;

//creates node with NULL children.
//to link nodes into trees, use insert()
Node * createNode(Value value, bool * errorCode);

//adds node to tree. first create root with createNode(...)
//then use root = insert(root,...)
Node * insert (Node * currentNode, Node * newNode);

//side = left to get left child, side = right to right child.
//returns NULL if there is no child.
Node * getChild(Node * node, Side side);

//gets value, returns NULL if node is NULL.
Value getValue(Node * node);