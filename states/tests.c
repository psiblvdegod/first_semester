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
    printStateAffiliation(graph);
}