#pragma once
#include <stdbool.h>

typedef struct Node Node;

typedef const char * Value;

typedef enum { left, right } Direction;

Node * createNode(Value value, bool * errorCode);

//returns NULL if value is not found
Value findValueByKey(Node * root, Value key);

//adds node to tree. first root with createNode(...)
//then use root = insert(root,...)
//requires external boolean variable with false value.
//isHeightChanged will be false after calling.
Node * insert(Node * root, Node * newNode, bool * isHeightChanged);

//requires external boolean variable with false value.
//isHeightChanged will be false after calling.
Node * dispose(Node * root, Value key, bool * isHeightChanged);

Node * getChild(Node * node, Direction side);

Value getValue(Node * node);