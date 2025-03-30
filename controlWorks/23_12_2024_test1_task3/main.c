#include "queue.h"
#include "commentsScan.h"
#include "test.h"

int main(void) {
    int errorCode = 0;
    queueTest(&errorCode);
    if (errorCode != 0) {
        return errorCode;
    }
    commentsScanTest(&errorCode);
    if (errorCode != 0) {
        return errorCode;
    }
    Queue *queue = scanCommentsFromFile("../text.txt", &errorCode);
    releaseQueue(&queue, &errorCode);
    deleteQueue(&queue, &errorCode);
}