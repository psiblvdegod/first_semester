#pragma once

#include "tree.h"
#include "stack.h"
#include <stdio.h>

//fills tree with example from file.
//operations are presented as numbers according to their numbers in ASCII table.
Tree * buildTree(FILE * stream, bool * errorCode);

//prints in prefix notation
void printAllNodes(Node * node, bool * errorCode);

void doSymmetricalTraversal(Node * node, Node * traversalResult[], int * index, bool * errorCode);

int calculateTreeExample(Tree * tree, bool * errorCode);