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

// turns city to capital.
void setCapital(Graph graph, Value city, bool *errorCode);

// attaches the nearest free city to the state.
void conquerNearestCity(Graph graph, Value state, bool *errorCode);

// prints all vertices, which are considered capitals.
void printCapitals(Graph graph);

// prints adjacency matrix.
void printMatrix(Graph graph);

// prints adjacency lists for every vertex in the graph.
void printAdjacencyLists(Graph graph);

// prints capitals and cities belong to them and free cities.
void printStateAffiliation(Graph graph);
