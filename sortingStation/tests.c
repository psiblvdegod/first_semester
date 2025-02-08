#include "sortingStation.h"
#include "stack.h"
#include "queue.h"
#include <stdlib.h>

bool queueTest() {
    bool errorCode = false;
    Queue *testQueue = createQueue(&errorCode);
    if (testQueue == NULL) {
        return false;
    }
    enqueue(testQueue, '1', &errorCode);
    bool isEmptyTest = !isEmptyQueue(testQueue);
    return dequeue(testQueue, &errorCode) == '1' && isEmptyTest && !errorCode;
}

bool stackTest() {
    bool errorCode = false;
    Stack *stack = createStack(&errorCode);
    push(stack, '1', &errorCode);
    bool isEmptyTest = !isEmptyStack(stack);
    return pop(stack, &errorCode) == '1' && isEmptyTest && !errorCode;
}

bool sortingStationTest() {
    const char *input = "( 1 - 2) *(3+4)/ 5 ";
    const char *expectedResult = "1 2 - 3 4 + * 5 /";
    bool errorCode = false;

    Stack *stack = createStack(&errorCode);
    Queue *queue = createQueue(&errorCode);
    if (errorCode) {
        return false;
    }

    convertInfixToPostfix(input, stack, queue, &errorCode);
    if (errorCode) {
        return false;
    }

    for (int i = 0; expectedResult[i] != '\0'; ++i) {
        if (expectedResult[i] != dequeue(queue, &errorCode) || errorCode) {
            return false;
        }
    }
    return true;
}
