#pragma once

#include "tree.h"
#include "stack.h"
#include <stdio.h>

//fills the tree with example from file.
//operations are presented as numbers according to their numbers in ASCII table.
//every operation-node has both children, number-nodes don't.
//(if input stream is correct).
Tree * buildTree(FILE * stream, bool * errorCode);

//prints in prefix notation.
//distinguishes the number from the operation by
//checking for the presence of leftChild.
void printAllNodes(Node * node, bool * errorCode);

int calculateTree(Node * root, bool * errorCode);