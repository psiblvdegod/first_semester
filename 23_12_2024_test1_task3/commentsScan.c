#include "commentsScan.h"
#include <stdio.h>

Queue *scanCommentsFromFile(const char *filePath, int *errorCode) {
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
        if (readingStatus) {
            enqueue(queue, symbol, errorCode);
        }
        if (symbol == ';') {
            readingStatus = true;
        }
        if (symbol == '\n') {
            readingStatus = false;
        }
    }
    fclose(file);
    deleteQueue(&queue, errorCode);
    return queue;
}

void releaseQueue(Queue *queue, int *errorCode) {
    if (queue == NULL) {
        *errorCode = 1;
        return;
    }
    while (!isEmptyQueue(queue)) {
        printf("%c", dequeue(queue, errorCode));
    }
}