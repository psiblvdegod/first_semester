#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex {
    bool isCapital;
    Value state;
} Vertex;

typedef struct GraphInternals {
    int **adjacencyMatrix;
    int verticesAmount;
    Vertex **vertices;
} GraphInternals;

Vertex *createVertex(bool *errorCode) {
    Vertex *vertex = calloc(1, sizeof(Vertex));
    if (vertex == NULL) {
        *errorCode = true;
        return NULL;
    }
    vertex->isCapital = false;
    vertex->state = 0;
    return vertex;
}

Graph createGraph(int verticesAmount, bool *errorCode) {
    Graph graph = calloc(1, sizeof(GraphInternals));
    if (graph == NULL) {
        *errorCode = true;
        return NULL;
    }
    graph->verticesAmount = verticesAmount;
    graph->adjacencyMatrix = calloc(verticesAmount, sizeof(int*));

    for (int i = 0; i < verticesAmount; ++i) {
        graph->adjacencyMatrix[i] = calloc(verticesAmount, sizeof(int));
    }

    graph->vertices = calloc(verticesAmount, sizeof(Vertex));
    if (graph->adjacencyMatrix == NULL || graph->vertices == NULL) {
        *errorCode = true;
    }
    return graph;
}

Graph buildGraph(const char * filePath, bool *errorCode) {
    FILE * file = fopen(filePath, "r");
    if (file == NULL) {
        *errorCode = true;
        return NULL;
    }

    int citiesAmount;
    int roadsAmount;
    fscanf(file, "%d%d", &citiesAmount, &roadsAmount);
    Graph graph = createGraph(citiesAmount, errorCode);
    if (*errorCode) {
        return NULL;
    }

    for (int p = 0; p < citiesAmount; ++p) {
        graph->vertices[p] = createVertex(errorCode);
    }
    if (*errorCode) {
        return NULL;
    }
    for (int l = 0; l < roadsAmount; ++l) {
        int i, j, length;
        fscanf(file, "%d%d%d", &i, &j, &length);
        graph->adjacencyMatrix[i][j] = length;
        graph->adjacencyMatrix[j][i] = length;
    }

    int capitalsAmount;
    fscanf(file, "%d", &capitalsAmount);
    for (int k = 0; k < capitalsAmount; ++k) {
        int capital;
        fscanf(file, "%d", &capital);
        graph->vertices[capital]->isCapital = true;
        graph->vertices[capital]->state = capital;
    }
    return graph;
}

void addNearestCity(Vertex **cities, Vertex *capital, bool *errorCode) {
    Vertex * nearestCity = *cities;
}

/*
typedef struct Edge {
    Vertex * vertex1;
    Vertex * vertex2;
    Value value;
} Edge;

Edge * createEdge(Vertex * vertex1, Vertex * vertex2, Value value, bool * errorCode) {
    Edge * edge = calloc(1, sizeof(Edge));
    if (edge == NULL) {
        *errorCode = true;
        return NULL;
    }
    edge->value = value;
    edge->vertex1 = vertex1;
    edge->vertex2 = vertex2;
    return edge;
}*/