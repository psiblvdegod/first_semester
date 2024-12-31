#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include "graph.h"

// tests functions from module graph.c
int graphTests();

// tests buildGraph() using data from <filePath>
int buildGraphTests(const char *filePath);