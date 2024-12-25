#pragma once

typedef int Value;

typedef struct Node Node;

typedef struct List List;

// creates empty list
List *createList(int *errorCode);

// adds value to the list
void addToList(List *list, Value value, int *errorCode);

// deletes the node following the current one
void deleteNext(List *list, Node *node, int *errorCode);

// frees allocated memory and turns pointer NULL
void deleteList(List **list, int *errorCode);

// returns first node of the list
Node *getHead(List *list, int *errorCode);

// return the node following the current one
Node *getNext(Node *node, int *errorCode);

// returns the value from the node
Value getValue(Node *node, int *errorCode);