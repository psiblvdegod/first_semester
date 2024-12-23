#pragma once

#include <stdbool.h>
#include <stdlib.h>

typedef int Value;

typedef struct Node Node;

Node *createNode(Value value, int *errorCode);

Node *create(int size, int *errorCode);

Node *getNext(Node *node, int *errorCode);

Node *delete(Node *node, int *errorCode);

Value getValue(Node *node, int *errorCode);