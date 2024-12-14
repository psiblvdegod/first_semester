#include "shortestWay.h"
#include "graph.h"

typedef int QueueValue;

struct Queue {
    QueueValue value;
    struct Queue * previous;
};

typedef struct Queue* Queue;

void enqueue();

void dequeue();

int findShortestWayLength(Graph graph, const int vertex, const int state, bool *errorCode);