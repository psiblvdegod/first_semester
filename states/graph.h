#pragma once
#include "list.h"
#include <stdlib.h>

typedef struct Graph Graph;

Graph *createGraph(Value verticesAmount, int *errorCode);

void deleteGraph(Graph **graph, int *errorCode);

void printAdjacencyLists(Graph *graph, int *errorCode);

typedef struct Matrix Matrix;

Matrix *buildAdjacencyMatrix(Graph *graph, int *errorCode);

void deleteMatrix(Matrix **matrix, int *errorCode);

void printMatrix(Matrix *matrix, int *errorCode);