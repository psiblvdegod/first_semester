#pragma once
#include "tree.h"
#include "stack.h"
#include <stdio.h>

// opens file for read,
// fills the tree with expression from file,
// operations are presented as numbers according to their numbers in ASCII table,
// operation can be distinguished from number using getChild(),
// every operation-node has both children, number-nodes don't,
// stops process, deletes tree and reports an error if expression in file is incorrect.
Node *buildTree(const char *filePath, int *errorCode);

// calculates expression doing traversal.
int calculateTree(Node *root, int *errorCode);

// prints expression in prefix notation.
void printTree(Node *root, int *errorCode);