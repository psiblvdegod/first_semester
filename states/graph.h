#pragma once
#include <stdbool.h>

typedef int Value;

typedef struct GraphInternals* Graph;

Graph buildGraph(const char *filePath, bool *errorCode);

void printCapitals(Graph graph);

void printMatrix(Graph graph);

void printAdjacencyLists(Graph graph);