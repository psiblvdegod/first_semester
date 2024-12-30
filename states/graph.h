#pragma once
#include "list.h"
#include <stdlib.h>

typedef struct Graph Graph;

Graph *createGraph(Value verticesAmount, int *errorCode);

void deleteGraph(Graph **graph, int *errorCode);

Graph *buildGraph(const char *filePath, int *errorCode);

void printAdjacencyLists(Graph *graph, int *errorCode);