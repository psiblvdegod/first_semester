#pragma once

#include "typeDefinitions.h"
#include <stdbool.h>

Value searchInTree(Node *node, Key key, int *errorCode);

void insertIntoTree(Node **root, Value value, Key key, int *errorCode);

void deleteFromTree(Node **root, Key key, int *errorCode);

void deleteTree(Node **root, int *errorCode);