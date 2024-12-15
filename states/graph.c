#include "graph.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex {
    Value state;
    Value number;
    bool isCapital;
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

Node *addNode(Node *previous, Vertex* vertex) {
    Node *node = calloc(1, sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->previous = previous;
    node->vertex = vertex;
    return node;
}

Vertex *createVertex(Value number, bool *errorCode) {
    Vertex *vertex = calloc(1, sizeof(Vertex));
    if (vertex == NULL) {
        *errorCode = true;
        return NULL;
    }
    vertex->number = number;
    vertex->isCapital = false;
    vertex->state = -1;
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
    for (int n = 0; n < verticesAmount; ++n) {
        graph->vertices[n] = createVertex(n, errorCode);
        if (*errorCode) {
            return NULL;
        }
    }
    return graph;
}

Graph buildGraph(const char *filePath, bool *errorCode) {
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

    if (*errorCode) {
        return NULL;
    }
    for (int l = 0; l < roadsAmount; ++l) {
        int i, j, length;
        fscanf(file, "%d%d%d", &i, &j, &length);
        graph->adjacencyMatrix[i][j] = length;
        graph->adjacencyMatrix[j][i] = length;
        graph->vertices[i]->linkedVertices = addNode(graph->vertices[i]->linkedVertices, graph->vertices[j]);
        graph->vertices[j]->linkedVertices = addNode(graph->vertices[j]->linkedVertices, graph->vertices[i]);

    }

    int capitalsAmount = 0;
    fscanf(file, "%d", &capitalsAmount);
    for (int k = 0; k < capitalsAmount; ++k) {
        int capital = 0;
        fscanf(file, "%d", &capital);
        graph->vertices[capital]->isCapital = true;
        graph->vertices[capital]->state = capital;
    }
    fclose(file);
    return graph;
}

void printCapitals(Graph graph) {
    Vertex **vertices = graph->vertices;
    for (int i = 0; i < graph->verticesAmount; ++i) {
        printf("%d - %d\n", i, vertices[i]->isCapital);
    }
}

void printMatrix(Graph graph) {
    int **matrix = graph->adjacencyMatrix;
    for (int i = 0; i < graph->verticesAmount; ++i) {
        for (int j = 0; j < graph->verticesAmount; ++j) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

void printAdjacencyLists(Graph graph) {
    for (int i = 0; i < graph->verticesAmount; ++i) {
        Vertex *vertex = graph->vertices[i];
        printf("%d: ", vertex->number);
        Node *node = vertex->linkedVertices;
        while (node != NULL) {
            printf("%d ", node->vertex->number);
            node = node->previous;
        }
        printf("\n");
    }
}

void doWidthTraversal(Graph graph, Vertex *startingVertex, bool *errorCode) {
    bool *isVertexVisited = calloc(graph->verticesAmount, sizeof(bool));
    Queue queue = createQueue();
    if (isVertexVisited == NULL || queue == NULL) {
        *errorCode = true;
        return;
    }
    enqueue(queue, startingVertex);
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

void test(Graph graph, bool *errorCode) {
    doWidthTraversal(graph, graph->vertices[1], errorCode);
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