#include "queue.h"
#include "commentsScan.h"
#include "test.h"

int main(void) {
    int errorCode = 0;

    Queue *queue = scanCommentsFromFile("../text.txt", &errorCode);
    releaseQueue(queue, &errorCode);
    deleteQueue(&queue, &errorCode);
}
