#include "fileProcessing.h"
#include "tests.h"
#include "errorCode.h"

int graphTests() {
    int errorCode = NO_ERRORS;
    Graph *graph =  buildGraph("../text.txt", &errorCode);
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