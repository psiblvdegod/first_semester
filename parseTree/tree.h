#pragma once
#include <stdbool.h>

typedef struct Node Node;

typedef int Value;

//child's position for addChild() and getChild()
typedef enum {
    left,
    right
} Position;

Node *createNode(Value value, int *errorCode);

void addChild(Node *parent, Node *child, Position position, int *errorCode);

Node *getChild(Node *parent, Position position, int *errorCode);

Value getValue(Node *node, int *errorCode);

void deleteTree(Node **root, int *errorCode);