#include <stdio.h>
#include <stdbool.h>
#include "errorCode.h"
#include "tests.h"
#include "graph.h"

int main(void) {
    int errorCode = NO_ERRORS;
    Graph *graph =  buildGraph("../test.txt", &errorCode);
    return errorCode;
}
