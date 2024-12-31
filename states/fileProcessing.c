#include "fileProcessing.h"
#include "errorCode.h"
#include "errno.h"
#include <stdio.h>

void setEdge(Graph *graph, Value number1, Value number2, Value edgeLength, int *errorCode);

void distributeCities(Graph *graph, int *errorCode);

void setCapital(Graph *graph, Value city, int *errorCode);

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