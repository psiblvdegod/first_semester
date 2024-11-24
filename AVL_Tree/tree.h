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

Value getKey(Node * node, bool * errorCode);

//if there isn't node with such key, returns NULL
Node * getNodeByKey(Node * root, Value key, bool * errorCode);


Node * doSmallRotation(Node * node, Side direction, bool * errorCode);

Node * doBigRotation(Node * node, Side direction, bool * errorCode);

Node * insert(Node * root, Node * newNode, bool * errorCode);

Node *deleteNode(Node * root, Value key, bool * errorCode);