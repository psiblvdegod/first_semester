#include "fileProcessing.h"
#include "tests.h"
#include "errorCode.h"

int graphTests() {
    int errorCode = NO_ERRORS;
    Graph *graph =  buildGraph("../text.txt", &errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    Matrix *matrix = buildAdjacencyMatrix(graph, &errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    printMatrix(matrix, &errorCode);
    deleteGraph(&graph, &errorCode);
    deleteMatrix(&matrix, &errorCode);
}