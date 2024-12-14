#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "graph.h"

int main(void) {
    bool errorCode = false;
    Graph graph = buildGraph("../text.txt", &errorCode);
    //printCapitals(graph);
    printMatrix(graph);
    int a = 0;
}
