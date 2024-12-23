#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Queue *giveComments(const char *filePath, int *errorCode) {
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
    bool status = false;
    while (true) {
        const char symbol = (char) fgetc(file);
        if (status) {
            enqueue(queue, symbol, errorCode);
        }
        if (symbol == ';') {
            status = true;
        }
        if (symbol == '\n') {
            status = false;
        }
        if (symbol == EOF) {
            break;
        }
    }
    return queue;
}

void printQueue(Queue *queue, int *errorCode) {
    if (queue == NULL) {
        *errorCode = 1;
        return;
    }
    while (!isEmptyQueue(queue)) {
        printf("%c", dequeue(queue, errorCode));
    }
}

int main(void) {
    int errorCode = 0;
    Queue *queue = giveComments("../text.txt", &errorCode);
    printQueue(queue, &errorCode);
}
