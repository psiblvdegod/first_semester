#include "errorCode.h"
#include "errno.h"
#include "graph.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex {
    size_t number;
    size_t state;
    bool isCapital;
    struct List *linkedVertices;
} Vertex;

typedef struct List {
    Vertex *vertex;
    size_t distance;
    struct List *previous;
} List;

struct Graph {
    Vertex **vertices;
    size_t verticesAmount;
};

List *createElement(Vertex *vertex, size_t distance, int *errorCode) {
    if (vertex == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return NULL;
    }
    List *newElement = calloc(1, sizeof(List));
    if (newElement == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }
    newElement->vertex = vertex;
    newElement->distance = distance;
    return newElement;
}

List *addElement(List *list, List *newElement, int *errorCode) {
    if (newElement == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return NULL;
    }
    newElement->previous = list;
    return newElement;
}

List *findElement(List *list, size_t number, int *errorCode) {
    while (list != NULL) {
        if (list->vertex == NULL) {
            *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
            return NULL;
        }
        if (list->vertex->number == number) {
            return list;
        }
        list = list->previous;
    }
    return NULL;
}

Vertex *createVertex(size_t number, int *errorCode) {
    Vertex *vertex = calloc(1, sizeof(Vertex));
    if (vertex == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }
    vertex->number = number;
    vertex->state = -1;
    return vertex;
}

Graph *createGraph(const size_t verticesAmount, int *errorCode) {
    if (verticesAmount < 1) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return NULL;
    }
    Graph *graph = calloc(1, sizeof(Graph));
    if (graph == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }
    graph->verticesAmount = verticesAmount;
    graph->vertices = calloc(verticesAmount, sizeof(Vertex));
    if (graph->vertices == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        free(graph);
        return NULL;
    }
    for (size_t i = 0; i < verticesAmount; ++i) {
        graph->vertices[i] = createVertex(i, errorCode);
        if (*errorCode != NO_ERRORS) {
            for (size_t k = i; ; --k) {
                free(graph->vertices[k]);
                if (k == 0) {
                    break;
                }
            }
            free(graph->vertices);
            free(graph);
            return NULL;
        }
    }
    return graph;
}

void verifyGraphInvariants(Graph *graph, int *errorCode) {
    if (graph == NULL) {
        *errorCode = INVARIANT_VIOLATION;
        return;
    }
    if (graph->vertices == NULL) {
        *errorCode = INVARIANT_VIOLATION;
        return;
    }
    if (graph->verticesAmount < 1) {
        *errorCode = INVARIANT_VIOLATION;
        return;
    }
}

void setEdge(Graph *graph, const size_t number1, const size_t number2, const size_t edgeLength, int *errorCode) {
    verifyGraphInvariants(graph, errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    List *linkedWithFirst = graph->vertices[number1]->linkedVertices;
    List *linkedWithSecond = graph->vertices[number2]->linkedVertices;
    if (findElement(linkedWithFirst, number2, errorCode) != NULL || findElement(linkedWithSecond, number1, errorCode) != NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
        // an attempt to establish an existing edge
    }
    List *vertex1 = createElement(graph->vertices[number1], edgeLength, errorCode);
    List *vertex2 = createElement(graph->vertices[number2], edgeLength, errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    addElement(linkedWithFirst, vertex2, errorCode);
    addElement(linkedWithSecond, vertex1, errorCode);
}

void setCapital(Graph *graph, const size_t city, int *errorCode) {
    verifyGraphInvariants(graph, errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    graph->vertices[city]->isCapital = true;
    graph->vertices[city]->state = city;
}

void distributeCities(Graph *graph, const size_t capitalsAmount, int *errorCode) {
    verifyGraphInvariants(graph, errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    if (capitalsAmount < 1) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    size_t *capitals = calloc(capitalsAmount, sizeof(size_t));
    if (capitals == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return;
    }
    for (int i = 0, j = 0; i < graph->verticesAmount; ++i) {
        if (graph->vertices[i]->isCapital) {
            capitals[j] = i;
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

size_t scanNumber(FILE *file, int *errorCode) {
    char buffer[16] = {'0'};
    if (fscanf(file, "%s", buffer) != 1) {
        *errorCode = INCORRECT_EXPRESSION_IN_FILE;
        return 0;
    }
    size_t result = strtoul(buffer, NULL, 10);
    if (errno != 0) {
        *errorCode = INCORRECT_EXPRESSION_IN_FILE;
        errno = 0;
        return 0;
    }
    return result;
}

Graph *buildGraph(const char *filePath, int *errorCode) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        *errorCode = FILE_OPENING_ERROR;
        return NULL;
    }
    const Value verticesAmount = scanNumber(file, errorCode);
    const Value edgesAmount = scanNumber(file, errorCode);
    if (*errorCode != NO_ERRORS) {
        fclose(file);
        return NULL;
    }
    Graph *graph = createGraph(verticesAmount, errorCode);
    if (*errorCode != NO_ERRORS) {
        fclose(file);
        return NULL;
    }
    for (size_t i = 0; i < edgesAmount; ++i) {
        const Value vertex1 = scanNumber(file, errorCode);
        const Value vertex2 = scanNumber(file, errorCode);
        const Value length = scanNumber(file, errorCode);
        setEdge(graph, vertex1, vertex2, length, errorCode);
        if (*errorCode != NO_ERRORS) {
            fclose(file);
            deleteGraph(&graph, errorCode);
            return NULL;
        }
    }
    const size_t capitalsAmount = scanNumber(file, errorCode);
    for (size_t k = 0; k < capitalsAmount; ++k) {
        const size_t capital = scanNumber(file, errorCode);
        setCapital(graph, capital, errorCode);
    }
    distributeCities(graph, capitalsAmount, errorCode);
    fclose(file);
    return graph;
}
/*
int* findShortestWay(Graph *graph, const int startingVertex, bool *errorCode) {
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

void conquerNearestCity(Graph *graph, const int state, bool *errorCode) {
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
*/
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
    int freeCitiesAmount = graph->verticesAmount;
    for (int i = 0; i < graph->verticesAmount; ++i) {
        if (!cities[i]->isCapital) {
            continue;
        }
        printf("%d : ", cities[i]->number);
        --freeCitiesAmount;
        for (int j = 0; j < graph->verticesAmount; ++j) {
            if (cities[j]->state == cities[i]->state) {
                printf("%d ", cities[j]->number);
                --freeCitiesAmount;
            }
        }
        printf("\n");
    }
    if (freeCitiesAmount > 0) {
        printf("free cities: ");
        for (int i = 0; i < graph->verticesAmount; ++i) {
            if (cities[i]->state == -1) {
                printf("%d ", cities[i]->number);
            }
        }
    }
    printf("\n");
}

void distributeCities_(Graph *graph, int *errorCode) {
    verifyGraphInvariants(graph, errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    List **states = calloc(graph->verticesAmount, sizeof(List*));
    if (states == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return;
    }
    for (size_t i = 0; i < graph->verticesAmount; ++i) {
        if (graph->vertices[i]->isCapital) {
            List *linked = graph->vertices[i]->linkedVertices;
            while (linked != NULL) {

            }
        }
    }
    for (int i = 0; i < graph->verticesAmount; ++i) {
        if (states[i] == NULL) {
            continue;
        }
        List *list = states[i];
        List *closestCity = NULL;
        size_t minDist = list->distance;
        while (list != NULL) {
            if (minDist > list->distance) {
                closestCity = list;
                minDist = list->distance;
            }
            list = list->previous;
        }
        states[i]->vertex->state = i;
    }
}