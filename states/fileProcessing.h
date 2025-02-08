#pragma once

#include "graph.h"

// opens file for read,
// builds and returns graph according to data in file.
Graph *buildGraph(const char *filePath, int *errorCode);