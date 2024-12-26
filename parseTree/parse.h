#pragma once
#include "tree.h"
#include "stack.h"
#include <stdio.h>

//fills the tree with example from file.
//operations are presented as numbers according to their numbers in ASCII table.
//every operation-node has both children, number-nodes don't.
//(if input stream is correct).
Node *buildTree(const char *filePath, int *errorCode);

int calculateTree(Node *root, int *errorCode);