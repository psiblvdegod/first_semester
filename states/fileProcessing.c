#include "fileProcessing.h"
#include "errorCode.h"
#include "errno.h"
#include <stdio.h>

Value scanNumber(FILE *file, int *errorCode) {
    char buffer[16] = {'0'};
    if (fscanf(file, "%s", buffer) != 1) {
        *errorCode = INCORRECT_EXPRESSION_IN_FILE;
        return 0;
    }
    Value result = strtoul(buffer, nullptr, 10);
    if (errno != 0) {
        *errorCode = INCORRECT_EXPRESSION_IN_FILE;
        errno = 0;
        return 0;
    }
    return result;
}

Graph *buildGraph(const char *filePath, int *errorCode) {
    FILE *file = fopen(filePath, "r");
    if (file == nullptr) {
        *errorCode = FILE_OPENING_ERROR;
        return nullptr;
    }
    const Value verticesAmount = scanNumber(file, errorCode);
    const Value edgesAmount = scanNumber(file, errorCode);
    if (*errorCode != NO_ERRORS) {
        fclose(file);
        return nullptr;
    }
    Graph *graph = createGraph(verticesAmount, errorCode);
    if (*errorCode != NO_ERRORS) {
        fclose(file);
        return nullptr;
    }
    for (Value i = 0; i < edgesAmount; ++i) {
        const Value vertex1 = scanNumber(file, errorCode);
        const Value vertex2 = scanNumber(file, errorCode);
        const Value length = scanNumber(file, errorCode);
        if (*errorCode != NO_ERRORS) {
            fclose(file);
            deleteGraph(&graph, errorCode);
            return nullptr;
        }
        setEdge(graph, vertex1, vertex2, length, errorCode);
        if (*errorCode != NO_ERRORS) {
            fclose(file);
            deleteGraph(&graph, errorCode);
            return nullptr;
        }
    }
    const size_t capitalsAmount = scanNumber(file, errorCode);
    if (*errorCode != NO_ERRORS) {
        fclose(file);
        deleteGraph(&graph, errorCode);
        return nullptr;
    }
    for (size_t k = 0; k < capitalsAmount; ++k) {
        const size_t capital = scanNumber(file, errorCode);
        setCapital(graph, capital, errorCode);
        if (*errorCode != NO_ERRORS) {
            fclose(file);
            deleteGraph(&graph, errorCode);
            return nullptr;
        }
    }
    fclose(file);
    if (*errorCode != NO_ERRORS) {
        deleteGraph(&graph, errorCode);
        return nullptr;
    }
    distributeCities(graph, errorCode);
    if (*errorCode != NO_ERRORS) {
        deleteGraph(&graph, errorCode);
    }
    return graph;
}