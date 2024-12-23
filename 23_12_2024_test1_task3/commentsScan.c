#include "commentsScan.h"
#include <stdio.h>

Queue *scanCommentsFromFile(const char *filePath, int *errorCode) {
    if (filePath == NULL) {
        *errorCode = 1;
        return NULL;
    }
    Queue *queue = createQueue(errorCode);
    if (*errorCode) {
        deleteQueue(&queue, errorCode);
        return NULL;
    }
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        *errorCode = 6;
        fclose(file);
        deleteQueue(&queue, errorCode);
        return NULL;
    }
    bool readingStatus = false;
    while (true) {
        const char symbol = (char)fgetc(file);
        if (symbol == EOF) {
            break;
        }
        if (symbol == ';') {
            readingStatus = true;
        }
        if (readingStatus) {
            enqueue(queue, symbol, errorCode);
        }
        if (symbol == '\n') {
            readingStatus = false;
        }
    }
    fclose(file);
    return queue;
}

void releaseQueue(Queue **queue, int *errorCode) {
    if (queue == NULL || *queue == NULL) {
        *errorCode = 1;
        return;
    }
    while (!isEmptyQueue(*queue)) {
        printf("%c", dequeue(*queue, errorCode));
    }
    deleteQueue(queue, errorCode);
}