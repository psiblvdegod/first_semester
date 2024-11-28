#pragma once
#include <stdbool.h>

typedef enum {
    left,
    right
} Side;

typedef struct Node Node;

typedef const char * Value;

Node * createNode(Value value, Value key, bool * errorCode);

Value getValue(Node * node, bool * errorCode);

Node * getValueByKey(Node * root, Value key, char ** result);

Node * doSmallRotation(Node * node, Side direction, bool * errorCode);

Node * doBigRotation(Node * node, Side direction, bool * errorCode);

Node * insert(Node * root, Node * newNode, bool * isHeightChanged);

Node * dispose(Node * root, Value key, bool * isHeightChanged);