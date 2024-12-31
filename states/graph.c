#include "errorCode.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex {
    Value number;
    long state;
    bool isCapital;
    struct List *linkedVertices;
} Vertex;

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
        graph->vertices[i] = calloc(1, sizeof(Vertex));
        if (graph->vertices[i] == NULL) {
            *errorCode = MEMORY_ALLOCATION_ERROR;
            deleteGraph(&graph, errorCode);
            return NULL;
        }
        graph->vertices[i]->linkedVertices = createList(errorCode);
        if (*errorCode != NO_ERRORS) {
            deleteGraph(&graph, errorCode);
            return NULL;
        }
        graph->vertices[i]->number = i;
        graph->vertices[i]->state = -1;
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
    if (graph == NULL || *graph == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    if ((*graph)->vertices != NULL) {
        for (Value i = 0; i < (*graph)->verticesAmount; ++i) {
            if ((*graph)->vertices[i] != NULL) {
                deleteList(&((*graph)->vertices[i]->linkedVertices), errorCode);
                free((*graph)->vertices[i]);
            }
        }
        free((*graph)->vertices);
    }
    free(*graph);
    *graph = NULL;
}

void setEdge(Graph *graph, const Value number1, const Value number2, const Value edgeLength, int *errorCode) {
    verifyGraphInvariants(graph, errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    if (number1 >= graph->verticesAmount || number2 >= graph->verticesAmount) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    List *linkedWithFirst = graph->vertices[number1]->linkedVertices;
    List *linkedWithSecond = graph->vertices[number2]->linkedVertices;
    if (searchInList(linkedWithFirst, number2, errorCode) || searchInList(linkedWithSecond, number1, errorCode)) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
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

typedef struct State {
    Value number;
    List *borderCities;
} State;

State **getStates(Graph *graph, Value *statesAmount, int *errorCode) {
    verifyGraphInvariants(graph, errorCode);
    if (*errorCode != NO_ERRORS) {
        return NULL;
    }
    for (Value i = 0; i < graph->verticesAmount; ++i) {
        if (graph->vertices[i]->isCapital) {
            ++(*statesAmount);
        }
    }
    State **states = calloc(*statesAmount, sizeof(State *));
    if (states == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }
    for (Value i = 0, j = 0; i < graph->verticesAmount; ++i) {
        if (graph->vertices[i]->isCapital) {
            states[j] = calloc(1, sizeof(State));
            states[j]->number = i;
            states[j]->borderCities = copyList(graph->vertices[i]->linkedVertices, errorCode);
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
    if (*errorCode != NO_ERRORS) {
        return 0;
    }
    Value result = 0;
    Value currentMinDistance = 0;
    while (current != NULL) {
        const Value number = getNumber(current, errorCode);
        const Value distance = getDistance(current, errorCode);
        if (*errorCode != NO_ERRORS) {
            return 0;
        }
        if (graph->vertices[number]->state == -1 && (distance < currentMinDistance || !(*wasFreeCityFound))) {
            currentMinDistance = distance;
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
    State **states = getStates(graph, &statesAmount, errorCode);
    if (*errorCode != NO_ERRORS) {
        for (Value i = 0; i < statesAmount; ++i) {
            deleteList(&states[i]->borderCities, errorCode);
            free(states[i]);
        }
        free(states);
        return;
    }
    for (Value i = 0, distributed = 0; distributed < statesAmount; ++i) {
        if (i == statesAmount) {
            i = 0;
        }
        if (states[i] == NULL) {
            continue;
        }
        bool wasFreeCityFound = false;
        const Value closestCity = findClosest(graph, states[i]->borderCities, &wasFreeCityFound, errorCode);
        if (!wasFreeCityFound) {
            ++distributed;
            free(states[i]->borderCities);
            free(states[i]);
            states[i] = NULL;
            continue;
        }
        graph->vertices[closestCity]->state = states[i]->number;
        List *copy = copyList(graph->vertices[closestCity]->linkedVertices, errorCode);
        ListElement *current = getHead(copy, errorCode);
        while (current != NULL) {
            addToList(states[i]->borderCities, getNumber(current, errorCode), getDistance(current, errorCode), errorCode);
            current = getNext(current, errorCode);
        }
    }
    free(states);
}

Value *getStateAffiliation(Graph *graph, Value *citiesAmount, int *errorCode) {
    verifyGraphInvariants(graph, errorCode);
    if (*errorCode != NO_ERRORS) {
        return NULL;
    }
    Value *stateAffiliation = calloc(graph->verticesAmount, sizeof(Value));
    if (stateAffiliation == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }
    for (Value i = 0; i < graph->verticesAmount; ++i) {
        stateAffiliation[i] = graph->vertices[i]->state;
    }
    if (citiesAmount != NULL) {
        *citiesAmount = graph->verticesAmount;
    }
    return stateAffiliation;
}