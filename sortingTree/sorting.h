#pragma once

#include "tree.h"
#include <stdio.h>

//fills the tree with example from file.
//operations are presented as numbers according to their numbers in ASCII table.
//every operation-node has both children, number-nodes don't.
//(if input stream is correct).
//Tree * buildTree(FILE * stream, bool * errorCode);

//prints in prefix notation.
//distinguishes the number from the operation by
//checking for the presence of leftChild.
void treeSort(Node * node, Value * array, int * external, bool * errorCode);
int calculateTree(Node * root, bool * errorCode);


//builds tree of array's values. returns root.
Node * buildTree(Value *array, int arraySize, bool * errorCode);