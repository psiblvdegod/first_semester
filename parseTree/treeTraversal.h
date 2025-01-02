#pragma once

#include "tree.h"
#include "queue.h"

// for tests
// creates empty queue and fills it with prefix notation of expression from parse tree
Queue *fillQueueWithTreeExpression(Node *root, int *errorCode);

// prints expression from parse tree in prefix notation
void printTree(Node *node, int *errorCode);