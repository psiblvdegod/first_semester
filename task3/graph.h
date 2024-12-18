#pragma once
#include <stdbool.h>

typedef int Value;

typedef struct Graph* Graph;

// opens file in filePath for read,
// reads vertices amount and creates graph,
// reads and sets edges,
// reads and sets capitals,
// distributes cities.
Graph buildGraph(const char *filePath, bool *errorCode);

// creates an empty graph with fixed size = verticesAmount,
// it stores array of vertices, vertices amount and adjacency matrix.
// initialises vertices with natural numbers [1 : verticesAmount].
Graph createGraph(int verticesAmount, bool *errorCode);

// links two vertices and puts edgeWeight to adjacency matrix.
void setEdge(Graph graph, Value vertex1, Value vertex2, Value edgeWeight, bool *errorCode);

void printAllVertices(Graph graph, bool *errorCode);