#include <stdio.h>
#include <stdbool.h>
#include "graph.h"

int main(void) {
    bool errorCode = false;
    Graph graph = buildGraph("../text.txt", &errorCode);
    printCapitals(graph);
    printf("\n");
    printMatrix(graph);
    printf("\n");
    printAdjacencyLists(graph);
    printf("\n");
    test(graph, &errorCode);
    printf("\nbreakpoint");
}
