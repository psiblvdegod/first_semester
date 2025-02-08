#include <stdio.h>
#include <stdbool.h>
#include "queue.h"

void rewrite(const int a, const int b, const char* file1path, const char* file2path, bool *errorCode) {
    FILE *file1 = fopen(file1path, "r");
    if (file1 == NULL) {
        *errorCode = true;
        fclose(file1);
        return;
    }
    Queue *queue1 = createQueue(errorCode);
    Queue *queue2 = createQueue(errorCode);
    if (*errorCode) {
        return;
    }
    while (true) {
        int buffer = 0;
        if (fscanf(file1, "%d", &buffer) != 1) {
            break;
        }
        if (buffer < a) {
            enqueue(queue1, buffer, errorCode);
        }
        else {
            enqueue(queue2, buffer, errorCode);
        }
        if (*errorCode) {
            return;
        }
    }
    FILE *file2 = fopen(file2path, "w");
    if (file2 == NULL) {
        *errorCode = true;
        fclose(file2);
        return;
    }
    while (!isEmptyQueue(queue1)) {
        fprintf(file2, "%d ", dequeue(queue1, errorCode));
    }
    while (!isEmptyQueue(queue2)) {
        const int buffer = dequeue(queue2, errorCode);
        if (buffer > b) {
            enqueue(queue1, buffer, errorCode);
        }
        else {
            fprintf(file2, "%d ", buffer);
        }
    }
    while (!isEmptyQueue(queue1)) {
        fprintf(file2, "%d ", dequeue(queue1, errorCode));

    }
    fclose(file1);
    fclose(file2);
}

int main(void) {
    bool errorCode = false;
    rewrite(0, 10, "../f.txt", "../g.txt", &errorCode);
}
