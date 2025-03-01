#pragma once

#include "tree.h"

// tests functions from stack.c module
int stackTests();

// tests insert() search() and delete() on AVL tree
int AVLTreeTest();

// tests verifyAVLTreeInvariants using data from <filePath>
int invariantTest(const char *filePath);

// tests functions from dictionary.c module
int dictionaryTest();

