#include "test.h"
#include "graph.h"
#include <stdlib.h>

bool graphTest() {
    bool errorCode = false;
    Graph graph = buildGraph("../text.txt", &errorCode);
    if (graph == NULL) {
        return false;
    }
    printAllVertices(graph, &errorCode);
    destroyGraph(&graph);
    return true;
}
