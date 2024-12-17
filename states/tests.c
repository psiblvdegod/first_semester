#include "tests.h"

bool graphTests() {
    bool errorCode = false;
    Graph graph = createGraph(3, &errorCode);
    if (graph == NULL) {
        return false;
    }

}