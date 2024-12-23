#include "commentsScan.h"
#include <stdio.h>

Queue *scanCommentsFromFile(const char *filePath, int *errorCode) {
    Queue *queue = createQueue(errorCode);
    if (*errorCode) {
        return NULL;
    }
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        *errorCode = 6;
        fclose(file);
        return NULL;
    }
    bool readingStatus = false;
    while (true) {
        const char symbol = (char) fgetc(file);
        if (readingStatus) {
            enqueue(queue, symbol, errorCode);
        }
        if (symbol == ';') {
            readingStatus = true;
        }
        else if (symbol == '\n') {
            readingStatus = false;
        }
        else if (symbol == EOF) {
            break;
        }
    }
    fclose(file);
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