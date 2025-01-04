#pragma once

#include <stdbool.h>
#include "AVL_Tree.h"

Value searchInTree(Node *root, Value key);

void insertIntoTree(Node **root, Value value, Key key, int *errorCode);

void deleteFromTree(Node **root, Key key, int *errorCode);