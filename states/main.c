#include <stdio.h>
#include <stdbool.h>
#include "graph.h"

void query_processing(const int user_query, Graph graph, bool *errorCode) {
    switch(user_query) {
        case 1:
            printCapitals(graph);
            break;
        case 2:
            printMatrix(graph);
            break;
        case 3:
            printAdjacencyLists(graph);
        case 4:
            printf("state?\n");
            int state = 0;
            scanf("%d", &state);
            conquerNearestCity(graph, state, errorCode);
        case 5:
            printStateAffiliation(graph);
    }
}

int main(void) {
    bool errorCode = false;
    Graph graph = buildGraph("../text.txt", &errorCode);
    int user_query = -1;
    while(user_query) {
        printf("1 - capitals. 2 - adj matrix. 3 - adj lists\n4 - conquer 5 - state affiliation\n");
        scanf("%d", &user_query);
        while(getchar() != '\n');
        query_processing(user_query, graph, &errorCode);
    }
}
