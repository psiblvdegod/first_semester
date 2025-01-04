#pragma once
#include <stdbool.h>

typedef struct Node Node;

typedef char *Value;

//returns NULL if value is not found
Value searchInTree(Node *root, Value key);

void insertIntoTree(Node **root, Value value, Value key, int *errorCode);

void deleteFromTree(Node **root, Value key, int *errorCode);