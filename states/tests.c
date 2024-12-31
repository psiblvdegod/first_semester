#include "fileProcessing.h"
#include "tests.h"
#include "errorCode.h"

int graphTests() {
    int errorCode = NO_ERRORS;
    const Value verticesAmount = 6;
    Graph *graph = createGraph(verticesAmount, &errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    setEdge(graph, 0, 1, 10, &errorCode);
    setEdge(graph, 0, 2, 10, &errorCode);
    setEdge(graph, 2, 3, 10, &errorCode);
    setEdge(graph, 4, 5, 10, &errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    setCapital(graph, 0, &errorCode);
    setCapital(graph, 4, &errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    distributeCities(graph, &errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    Value *stateAffiliation = getStateAffiliation(graph, NULL, &errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    deleteGraph(&graph, &errorCode);
    Value expectedResult[] = {0, 0, 0, 0, 4, 4};
    for (Value i = 0; i < verticesAmount; ++i) {
        if (expectedResult[i] != stateAffiliation[i]) {
            free(stateAffiliation);
            return TESTS_FAILED_ERROR;
        }
    }
    free(stateAffiliation);
    return errorCode;
}

int buildGraphTests(const char *filePath) {
    int errorCode = NO_ERRORS;
    Graph *graph =  buildGraph(filePath, &errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    Value citiesAmount = 0;
    Value *stateAffiliation = getStateAffiliation(graph, &citiesAmount, &errorCode);
    if (errorCode != NO_ERRORS) {
        deleteGraph(&graph, &errorCode);
        return errorCode;
    }
    Value expectedResult[] = {-1, 1, 1, 1, 4, 4, 4};
    for (Value i = 0; i < citiesAmount; ++i) {
        if (stateAffiliation[i] != expectedResult[i]) {
            free(stateAffiliation);
            return TESTS_FAILED_ERROR;
        }
    }
    free(stateAffiliation);
    return errorCode;
}