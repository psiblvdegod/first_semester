#pragma once
#include <stdbool.h>

typedef struct List List;

// list element
typedef struct Node Node;

typedef char *Value;

// creates empty list
List *createList(int *errorCode);

// adds element to the end of the list
void addToList(List *list, Value value, Value key, int *errorCode);

// frees allocated memory and turns pointer to NULL
void deleteList(List **list, int *errorCode);

// returns first element of the list
Node *getHead(List *list, int *errorCode);

// returns next element of the node (NULL if node is the last one)
Node *getNext(Node *node, int *errorCode);

// returns key
Value getKey(Node *node, int *errorCode);

// returns value
Value getValue(Node *node, int *errorCode);

// divides the list into two, returns head of the separated part.
List *splitList(List *list, int *errorCode);


