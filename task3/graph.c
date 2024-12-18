#pragma once
#include "graph.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex {
    Value number;
    struct Node *linkedVertices;
} Vertex;

typedef struct Node {
    Vertex *vertex;
    struct Node *previous;
} Node;

struct Graph {
    int **adjacencyMatrix;
    int verticesAmount;
    Vertex **vertices;
};

Node *addNode(Node *previous, Vertex* vertex, bool *errorCode) {
    Node *node = calloc(1, sizeof(Node));
    if (node == NULL) {
        *errorCode = true;
        return NULL;
    }
    node->previous = previous;
    node->vertex = vertex;
    return node;
}

Graph buildGraph(const char *filePath, bool *errorCode) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        *errorCode = true;
        return NULL;
    }
    int verticesAmount = 0;
    fscanf(file, "%d", &verticesAmount);
    Graph graph = createGraph(verticesAmount, errorCode);
    if (graph == NULL) {
        *errorCode = true;
        return NULL;
    }
    for (int i = 0; i < verticesAmount; ++i) {
        for (int j = 0; j < verticesAmount; ++j) {
            int edge = 0;
            fscanf(file, "%d", &edge);
            if (edge != 0) {
                graph->adjacencyMatrix[i][j] = 1;
                graph->vertices[i]->linkedVertices = addNode(graph->vertices[i]->linkedVertices, graph->vertices[j], errorCode);
            }
        }
    }
    return graph;
}


Vertex *createVertex(Value number, bool *errorCode) {
    Vertex *vertex = calloc(1, sizeof(Vertex));
    if (vertex == NULL) {
        *errorCode = true;
        return NULL;
    }
    vertex->number = number;
    vertex->linkedVertices = NULL;
    return vertex;
}

Graph createGraph(const int verticesAmount, bool *errorCode) {
    Graph graph = calloc(1, sizeof(struct Graph));
    if (graph == NULL) {
        *errorCode = true;
        return NULL;
    }
    graph->verticesAmount = verticesAmount;

    graph->adjacencyMatrix = calloc(verticesAmount, sizeof(int*));
    if (graph->adjacencyMatrix == NULL) {
        *errorCode = true;
        return NULL;
    }
    for (int i = 0; i < verticesAmount; ++i) {
        graph->adjacencyMatrix[i] = calloc(verticesAmount, sizeof(int));
        if (graph->adjacencyMatrix[i] == NULL) {
            *errorCode = true;
            return NULL;
        }
    }

    graph->vertices = calloc(verticesAmount, sizeof(Vertex));
    if (graph->vertices == NULL) {
        *errorCode = true;
        return NULL;
    }
    for (int i = 0; i < verticesAmount; ++i) {
        graph->vertices[i] = createVertex(i, errorCode);
        if (*errorCode) {
            return NULL;
        }
    }
    return graph;
}

void doWidthTraversal(Graph graph, bool *isVertexVisited, const int startingVertex, bool *errorCode) {
    Queue queue = createQueue();
    if (queue == NULL) {
        *errorCode = true;
        return;
    }

    enqueue(queue, graph->vertices[startingVertex]);
    while (!isQueueEmpty(queue)) {
        Vertex *currentVertex = dequeue(queue);
        printf("%d ", currentVertex->number);
        isVertexVisited[currentVertex->number] = true;
        Node *linkedVertices = currentVertex->linkedVertices;
        while(linkedVertices != NULL) {
            if (isVertexVisited[linkedVertices->vertex->number] == false) {
                enqueue(queue, linkedVertices->vertex);
            }
            linkedVertices = linkedVertices->previous;
        }
    }
}

void printAllVertices(Graph graph, bool *errorCode) {
    bool *isVertexVisited = calloc(graph->verticesAmount, sizeof(bool));
    if (isVertexVisited == NULL) {
        *errorCode = true;
        return;
    }
    for (int i = 0; i < graph->verticesAmount; ++i) {
        if (!isVertexVisited[i]) {
            doWidthTraversal(graph, isVertexVisited, i, errorCode);
        }
    }
}

void destroyGraph(Graph *graph) {
    if (*graph == NULL) {
        return;
    }
    if ((*graph)->adjacencyMatrix != NULL) {
        for (int i = 0; i < (*graph)->verticesAmount; ++i) {
            free((*graph)->adjacencyMatrix[i]);
        }
        free((*graph)->adjacencyMatrix);
    }
    if ((*graph)->vertices != NULL) {
        for (int i = 0; i < (*graph)->verticesAmount; ++i) {
            if ((*graph)->vertices[i] != NULL) {
                free((*graph)->vertices[i]->linkedVertices);
                free((*graph)->vertices[i]);
            }
        }
    }
    free(*graph);
    *graph = NULL;
}