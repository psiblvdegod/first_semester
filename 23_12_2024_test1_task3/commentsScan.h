#pragma once
#include "queue.h"

// opens file for read,
// scans it and puts strings which starts with ';' to queue
// closes file and returns queue.
Queue *scanCommentsFromFile(const char *filePath, int *errorCode);

// deletes all queue elements and prints em.
void releaseQueue(Queue *queue, int *errorCode);
