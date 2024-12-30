#include "errorCode.h"
#include "errno.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex {
    Value number;
    long state;
    bool isCapital;
    struct List *linkedVertices;
} Vertex;

Vertex *createVertex(const Value number, int *errorCode) {
    Vertex *vertex = calloc(1, sizeof(Vertex));
    if (vertex == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }
    vertex->number = number;
    vertex->state = -1;
    vertex->linkedVertices = createList(errorCode);
    return vertex;
}

struct Graph {
    Vertex **vertices;
    size_t verticesAmount;
};

Graph *createGraph(const Value verticesAmount, int *errorCode) {
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
    graph->vertices = calloc(verticesAmount, sizeof(Vertex *));
    if (graph->vertices == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        free(graph);
        return NULL;
    }
    for (Value i = 0; i < verticesAmount; ++i) {
        graph->vertices[i] = createVertex(i, errorCode);
        if (*errorCode != NO_ERRORS) {
            for (Value k = i; ; --k) {
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

void deleteGraph(Graph **graph, int *errorCode) {
    if (graph == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    verifyGraphInvariants(*graph, errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    for (Value i = 0; i < (*graph)->verticesAmount; ++i) {
        deleteList(&((*graph)->vertices[i]->linkedVertices), errorCode);
        free((*graph)->vertices[i]);
    }
    free((*graph)->vertices);
    free(*graph);
    *graph = NULL;
}

void setEdge(Graph *graph, const Value number1, const Value number2, const Value edgeLength, int *errorCode) {
    verifyGraphInvariants(graph, errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    List *linkedWithFirst = graph->vertices[number1]->linkedVertices;
    List *linkedWithSecond = graph->vertices[number2]->linkedVertices;
    if (searchInList(linkedWithFirst, number2, errorCode) || searchInList(linkedWithSecond, number1, errorCode)) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
        // an attempt to establish an existing edge
    }
    addToList(linkedWithFirst, number2, edgeLength, errorCode);
    addToList(linkedWithSecond, number1, edgeLength, errorCode);
}

void setCapital(Graph *graph, const Value city, int *errorCode) {
    verifyGraphInvariants(graph, errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    graph->vertices[city]->isCapital = true;
    graph->vertices[city]->state = city;
}

Value scanNumber(FILE *file, int *errorCode) {
    char buffer[16] = {'0'};
    if (fscanf(file, "%s", buffer) != 1) {
        *errorCode = INCORRECT_EXPRESSION_IN_FILE;
        return 0;
    }
    Value result = strtoul(buffer, NULL, 10);
    if (errno != 0) {
        *errorCode = INCORRECT_EXPRESSION_IN_FILE;
        errno = 0;
        return 0;
    }
    return result;
}

Vertex **getStates(Graph *graph, Value *statesAmount, int *errorCode) {
    verifyGraphInvariants(graph, errorCode);
    if (*errorCode != NO_ERRORS) {
        return NULL;
    }
    for (Value i = 0; i < graph->verticesAmount; ++i) {
        if (graph->vertices[i]->isCapital) {
            ++(*statesAmount);
        }
    }
    Vertex **states = calloc(*statesAmount, sizeof(Vertex *));
    if (states == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }
    for (Value i = 0, j = 0; i < graph->verticesAmount; ++i) {
        if (graph->vertices[i]->isCapital) {
            states[j] = createVertex(i, errorCode);
            states[j]->state = i;
            states[j]->linkedVertices = copyList(graph->vertices[i]->linkedVertices, errorCode);
            ++j;
        }
    }
    return states;
}

Value findClosest(Graph *graph, List *linkedVertices, bool *wasFreeCityFound, int *errorCode) {
    verifyGraphInvariants(graph, errorCode);
    if (*errorCode != NO_ERRORS) {
        return 0;
    }
    ListElement *current = getHead(linkedVertices, errorCode);
    Value result = 0;
    Value currentMinDistance = 0;
    while (current != NULL) {
        const Value number = getNumber(current, errorCode);
        const Value distance = getDistance(current, errorCode);
        if (*errorCode != NO_ERRORS) {
            return 0;
        }
        if (graph->vertices[number]->state == -1 && (distance < currentMinDistance || !(*wasFreeCityFound))) {
            currentMinDistance = (long)distance;
            result = number;
            *wasFreeCityFound = true;
        }
        current = getNext(current, errorCode);
    }
    return result;
}

void distributeCities(Graph *graph, int *errorCode) {
    verifyGraphInvariants(graph, errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    Value statesAmount = 0;
    Vertex **states = getStates(graph, &statesAmount, errorCode);
    if (*errorCode != NO_ERRORS) {
        for (Value i = 0; i < statesAmount; ++i) {
            deleteList(&states[i]->linkedVertices, errorCode);
            free(states[i]);
        }
        free(states);
        return;
    }
    for (Value i = 0, distributed = 0; distributed < statesAmount; i == statesAmount ? i = 0 : ++i) {
        if (states[i] == NULL) {
            continue;
        }
        bool wasFreeCityFound = false;
        const Value closestCity = findClosest(graph, states[i]->linkedVertices, &wasFreeCityFound, errorCode);
        if (!wasFreeCityFound) {
            ++distributed;
            free(states[i]->linkedVertices);
            free(states[i]);
            states[i] = NULL;
            continue;
        }
        graph->vertices[closestCity]->state = states[i]->state;
        List *copy = copyList(graph->vertices[closestCity]->linkedVertices, errorCode);
        ListElement *current = getHead(copy, errorCode);
        while (current != NULL) {
            addToList(states[i]->linkedVertices, getNumber(current, errorCode), getDistance(current, errorCode), errorCode);
            current = getNext(current, errorCode);
        }
    }
    free(states);
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
    for (Value i = 0; i < edgesAmount; ++i) {
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
    fclose(file);
    if (*errorCode != NO_ERRORS) {
        deleteGraph(&graph, errorCode);
        return NULL;
    }
    distributeCities(graph, errorCode);
    if (*errorCode != NO_ERRORS) {
        deleteGraph(&graph, errorCode);
    }
    return graph;
}

void printAdjacencyLists(Graph *graph, int *errorCode) {
    for (Value i = 0; i < graph->verticesAmount; ++i) {
        Vertex *vertex = graph->vertices[i];
        printf("%zu: ", vertex->number);
        printList(vertex->linkedVertices, errorCode);
        printf("\n");
    }
}

