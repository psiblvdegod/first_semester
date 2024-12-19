#include "tests.h"

bool graphTests() {
    bool errorCode = false;
    Graph graph = createGraph(3, &errorCode);
    if (graph == NULL) {
        return false;
    }
    setEdge(graph, 0, 1, 2, &errorCode);
    setEdge(graph, 1, 2, 12, &errorCode);
    setEdge(graph, 2, 0, 20, &errorCode);
    setCapital(graph, 1, &errorCode);
    conquerNearestCity(graph, 1, &errorCode);
    int size = 0;
    Value **adjacencyMatrix = getAdjacencyMatrix(graph, &size, &errorCode);
    if (errorCode) {
        return false;
    }
    const bool test1 = adjacencyMatrix[0][1] == 2;
    const bool test2 = adjacencyMatrix[2][1] == 12;
    const bool test3 = adjacencyMatrix[0][2] == 20;
    return test1 && test2 && test3 && !errorCode;
}