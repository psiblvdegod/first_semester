#pragma once
#include <stdbool.h>

typedef int Value;

typedef struct Graph* Graph;

// creates graph using createGraph() from graph.c,
// opens file in filePath for read,
// fills graph with
Graph buildGraph(const char *filePath, bool *errorCode);

// prints all vertices, which are considered capitals.
void printCapitals(Graph graph);

// prints adjacency matrix.
void printMatrix(Graph graph);

// prints adjacency lists for every vertex in the graph.
void printAdjacencyLists(Graph graph);

// garbage.
void test(Graph graph, bool *errorCode);

void conquerNearestCity(Graph graph, int state, bool *errorCode);

void printStateAffiliation(Graph graph);

Graph createGraph(int verticesAmount, bool *errorCode);

void setEdge(Graph graph, int city1, int city2, int edgeLength, bool *errorCode);

void setCapital(Graph graph, int city, bool *errorCode);