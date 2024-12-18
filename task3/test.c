#include "test.h"
#include "graph.h"
#include <stdlib.h>

bool graphTest() {
    bool errorCode = false;
    Graph graph = createGraph(3, &errorCode);
    if (graph == NULL) {
        return false;
    }
    destroyGraph(&graph);
}