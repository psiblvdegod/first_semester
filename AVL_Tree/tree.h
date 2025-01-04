#pragma once
#include <stdbool.h>

typedef struct Node Node;

typedef char *Value;

Node * createNode(Value value, Value key, int *errorCode);

//returns NULL if value is not found
Value search(Node * root, Value key);

//adds node to tree. first root with createNode(...)
//then use root = insert(root,...)
//requires external boolean variable with false value.
//isHeightChanged will be false after calling.
Node *insert(Node *node, Node *newNode, bool *isHeightChanged);

//requires external boolean variable with false value.
//isHeightChanged will be false after calling.
Node *dispose(Node * root, Value key, bool *isHeightChanged);