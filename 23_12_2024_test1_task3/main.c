#include "queue.h"
#include "commentsScan.h"

int main(void) {
    int errorCode = 0;
    Queue *queue = scanCommentsFromFile("../text.txt", &errorCode);
    printQueue(queue, &errorCode);
    deleteQueue(&queue, &errorCode);
}
