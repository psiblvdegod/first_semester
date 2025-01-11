#pragma once

#include <stdbool.h>

// tests functions from stack.c module
int stackTests();

// tests functions from tree.c module
int treeTests();

// tests buildTree() and calculateTree() using data from <filePath>
int parseTests(const char *filePath);

// tests functions from queue.c module
int queueTest();

// tests fillQueueWithTreeExpression()
int treeTraversalTest();