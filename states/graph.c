#include "graph.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex {
    Value number;
    Value state;
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
    for (int i = 0; i < verticesAmount; ++i) {
        graph->vertices[i] = createVertex(i, errorCode);
        if (*errorCode) {
            return NULL;
        }
    }
    return graph;
}

void setEdge(Graph graph, const int vertex1, const int vertex2, const int edgeLength, bool *errorCode) {
    if (graph == NULL || graph->vertices == NULL || graph->adjacencyMatrix == NULL) {
        *errorCode = true;
        return;
    }
    graph->vertices[vertex1]->linkedVertices = addNode(graph->vertices[vertex1]->linkedVertices, graph->vertices[vertex2], errorCode);
    graph->vertices[vertex2]->linkedVertices = addNode(graph->vertices[vertex2]->linkedVertices, graph->vertices[vertex1], errorCode);
    graph->adjacencyMatrix[vertex1][vertex2] = edgeLength;
    graph->adjacencyMatrix[vertex2][vertex1] = edgeLength;
}

void setCapital(Graph graph, const int city, bool *errorCode) {
    if (graph == NULL || graph->vertices == NULL) {
        *errorCode = true;
        return;
    }
    graph->vertices[city]->isCapital = true;
    graph->vertices[city]->state = city;
}

void distributeCities(Graph graph, const int capitalsAmount, bool *errorCode) {
    if (graph == NULL || capitalsAmount <= 0) {
        *errorCode = true;
        return;
    }
    int *capitals = calloc(capitalsAmount, sizeof(int));
    if (capitals == NULL) {
        *errorCode = true;
        return;
    }
    for (int i = 0, j = 0; i < graph->verticesAmount; ++i) {
        if (graph->vertices[i]->isCapital) {
            capitals[j] = graph->vertices[i]->number;
            ++j;
        }
    }
    for (int i = 0, j = 0;; i == capitalsAmount ? i = 0 : ++i) {
        bool isAllDistributed = true;
        for (; j < graph->verticesAmount; ++j) {
            if (graph->vertices[j]->state == -1) {
                graph->vertices[j]->state = capitals[i];
                isAllDistributed = false;
                break;
            }
        }
        if (isAllDistributed) {
            free(capitals);
            return;
        }
    }
}

Graph buildGraph(const char *filePath, bool *errorCode) {
    FILE * file = fopen(filePath, "r");
    if (file == NULL) {
        *errorCode = true;
        return NULL;
    }

    int verticesAmount;
    int edgesAmount;
    fscanf(file, "%d%d", &verticesAmount, &edgesAmount);
    Graph graph = createGraph(verticesAmount, errorCode);
    if (*errorCode) {
        return NULL;
    }

    for (int i = 0; i < edgesAmount; ++i) {
        int vertex1, vertex2, length;
        fscanf(file, "%d%d%d", &vertex1, &vertex2, &length);
        setEdge(graph, vertex1, vertex2, length, errorCode);
    }
    if (*errorCode) {
        return NULL;
    }

    Node *capitals = calloc(1, sizeof(Node));
    if (capitals == NULL) {
        *errorCode = true;
        return NULL;
    }
    int capitalsAmount = 0;
    fscanf(file, "%d", &capitalsAmount);
    for (int k = 0; k < capitalsAmount; ++k) {
        int capital = 0;
        fscanf(file, "%d", &capital);
        setCapital(graph, capital, errorCode);
    }
    distributeCities(graph, capitalsAmount, errorCode);
    fclose(file);
    return graph;
}

int* findShortestWay(Graph graph, const int startingVertex, bool *errorCode) {
    if (graph == NULL || graph->vertices == NULL || graph->adjacencyMatrix == NULL) {
        *errorCode = true;
        return NULL;
    }
    int **adjacencyMatrix = graph->adjacencyMatrix;

    int *isVertexVisited = calloc(graph->verticesAmount, sizeof(int));
    int *shortestWays = calloc(graph->verticesAmount, sizeof(int));
    Queue queue = createQueue();
    if (queue == NULL || isVertexVisited == NULL | shortestWays == NULL) {
        *errorCode = true;
        return NULL;
    }

    enqueue(queue, graph->vertices[startingVertex]);
    isVertexVisited[startingVertex] = 2;
    while (!isQueueEmpty(queue)) {
        Vertex *currentVertex = dequeue(queue);
        if (isVertexVisited[currentVertex->number] != 2) {
            isVertexVisited[currentVertex->number] = 1;
        }
        Node *linkedVertices = currentVertex->linkedVertices;
        bool isAll = true;
        while (linkedVertices != NULL) {
            const int number = linkedVertices->vertex->number;
            if (isVertexVisited[number] == 0) {
                isAll = false;
            }
            if (isVertexVisited[number] != 2) {
                enqueue(queue, linkedVertices->vertex);
                if (shortestWays[currentVertex->number] + adjacencyMatrix[number][currentVertex->number] < shortestWays[number] || shortestWays[number] == 0) {
                    shortestWays[number] = shortestWays[currentVertex->number] + adjacencyMatrix[number][currentVertex->number];
                }
            }
            linkedVertices = linkedVertices->previous;
        }
        if (isAll) {
            isVertexVisited[currentVertex->number] = 2;
        }
    }
    free(isVertexVisited);
    return shortestWays;
}

void conquerNearestCity(Graph graph, const int state, bool *errorCode) {
    if (graph == NULL || graph->vertices == NULL || state > graph->verticesAmount) {
        *errorCode = true;
        return;
    }
    Vertex **cities = graph->vertices;
    if (!cities[state]->isCapital) {
        return;
    }
    int newCity = -1;
    int newCityDistance = -1;
    for (int i = 0; i < graph->verticesAmount; ++i) {
        if (cities[i]->state != state) {
            continue;
        }

        int *shortestWays = findShortestWay(graph, i, errorCode);
        if (shortestWays == NULL || *errorCode) {
            *errorCode = true;
            return;
        }

        int nearestCity = -1;
        int nearestCityDistance = -1;
        for (int j = 0; j < graph->verticesAmount; ++j) {
            if (cities[j]->state != -1 || shortestWays[j] == 0) {
                continue;
            }
            if (nearestCity == -1 || shortestWays[j] < nearestCityDistance) {
                nearestCity = cities[j]->number;
                nearestCityDistance = shortestWays[j];
            }
        }

        if (newCity == -1 || nearestCityDistance < newCityDistance) {
            newCity = nearestCity;
            newCityDistance = nearestCityDistance;
        }

        free(shortestWays);
    }
    cities[newCity]->state = state;
}

void printCapitals(Graph graph) {
    Vertex **vertices = graph->vertices;
    printf("Capitals: ");
    for (int i = 0; i < graph->verticesAmount; ++i) {
        if (vertices[i]->isCapital) {
            printf("%d ", vertices[i]->number);
        }
    }
    printf("\n");
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

void printStateAffiliation(Graph graph) {
    Vertex **cities = graph->vertices;
    for (int i = 0; i < graph->verticesAmount; ++i) {
        if (!cities[i]->isCapital) {
            continue;
        }
        printf("%d : ", cities[i]->number);
        for (int j = 0; j < graph->verticesAmount; ++j) {
            if (cities[j]->state == cities[i]->state) {
                printf("%d ", cities[j]->number);
            }
        }
        printf("\n");
    }
    printf("free cities: ");
    for (int i = 0; i < graph->verticesAmount; ++i) {
        if (cities[i]->state == -1) {
            printf("%d ", cities[i]->number);
        }
    }
    printf("\n");
}