#include "graph.h"
#include <stdio.h>
#include "test.h"

int main(void) {
    if (!graphTest()) {
        printf("Error. Test failed.\n");
        return -1;
    }
    bool errorCode = false;
    const char *filePath = "../text.txt";
    Graph graph = buildGraph(filePath, &errorCode);
    if (errorCode) {
        printf("Something went wrong.\n");
    }
    printAllVertices(graph, &errorCode);
    if (errorCode) {
        printf("Something went wrong.\n");
    }
    destroyGraph(&graph);
}
