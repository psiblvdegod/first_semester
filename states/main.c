#include "fileProcessing.h"
#include "errorCode.h"
#include "tests.h"
#include "graph.h"

int main(void) {
    int errorCode = NO_ERRORS;
    Graph *graph =  buildGraph("../text.txt", &errorCode);
    return errorCode;
}