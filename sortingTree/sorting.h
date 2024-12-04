#pragma once

#include "tree.h"
#include <stdio.h>

//sorts array doing symmetricalTraversal.
//
void symmetricalTraversal(Node * node, Value * array, int * external, bool * errorCode);

//builds tree of array's values. returns root.
Node * buildTree(Value *array, int arraySize, bool * errorCode);

void treeSort(Value *array, const int arraySize, bool * errorCode);