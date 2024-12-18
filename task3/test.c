#include "test.h"
#include "graph.h"
#include <stdlib.h>

bool graphTest() {
    bool errorCode = false;
    const int verticesAmount = 3;
    Graph graph = createGraph(verticesAmount, &errorCode);
    if (graph == NULL) {
        return false;
    }
    bool *isAllVisited = printAllVertices(graph, &errorCode);
    for (int i = 0; i < verticesAmount; ++i) {
        if (isAllVisited[i] != true) {
            return false;
        }
    }
    destroyGraph(&graph);
    return true;
}