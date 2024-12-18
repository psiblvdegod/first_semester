#include "graph.h"

int main(void) {
    bool errorCode = false;
    const char *filePath = "../text.txt";
    Graph graph = buildGraph(filePath, &errorCode);
    printAllVertices(graph, &errorCode);
}
