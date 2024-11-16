#pragma once

#include "tree.h"
#include "stack.h"
#include <stdio.h>

Tree * buildTree(FILE * stream, bool * errorCode);

void printAllNodes(Node * node, bool * errorCode);

void doSymmetricalTraversal(Node * node, Node * traversalResult[], int * index, bool * errorCode);

int calculateTreeExample(Tree * tree, bool * errorCode);