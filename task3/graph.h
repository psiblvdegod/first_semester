#pragma once
#include <stdbool.h>

typedef int Value;

typedef struct Graph* Graph;

// opens file in filePath for read,
// reads amount of vertices,
// reads adjacency matrix
Graph buildGraph(const char *filePath, bool *errorCode);

// creates an empty graph with fixed size = verticesAmount,
// it stores array of vertices, vertices amount and adjacency matrix.
// initialises vertices with natural numbers [1 : verticesAmount].
Graph createGraph(int verticesAmount, bool *errorCode);

// prints all vertices doing width traversal from each vertex
bool *printAllVertices(Graph graph, bool *errorCode);

// frees all allocated memory
void destroyGraph(Graph *graph);