#pragma once
#include "list.h"
#include <stdlib.h>

typedef struct Graph Graph;

// creates graph with required amount of vertices
Graph *createGraph(Value verticesAmount, int *errorCode);

// sets edge between two vertices
void setEdge(Graph *graph, Value number1, Value number2, Value edgeLength, int *errorCode);

// turns city capital
void setCapital(Graph *graph, Value city, int *errorCode);

// adds cities to every state in turn
void distributeCities(Graph *graph, int *errorCode);

// frees allocated memory and turns pointer NULL
void deleteGraph(Graph **graph, int *errorCode);

// created for testing.
// returns array containing the affiliation of cities to states.
// index corresponds to the city number,
// value corresponds to the state to which the city belongs.
// puts amount of cities to variable "citiesAmount".
Value *getStateAffiliation(Graph *graph, Value *citiesAmount, int *errorCode);