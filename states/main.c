#include <stdio.h>
#include <stdbool.h>
#include "tests.h"
#include "graph.h"

int main(void) {
    bool errorCode = false;
    if (!graphTests()) {
        printf("Error. Tests failed.\n");
        return -1;
    }
    Graph graph = buildGraph("../text.txt", &errorCode);
    printStateAffiliation(graph);
    printf("\n");
    printAdjacencyLists(graph);
    printf("\n");
    printMatrix(graph);
}
