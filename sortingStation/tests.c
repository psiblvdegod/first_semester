#include "shuntingYardAlgorithm.h"

bool queueTest() {
    Queue * testQueue = createQueue();
    if (testQueue == NULL) {
        return false;
    }
    int errorCode = 0;
    enqueue(testQueue, 100, &errorCode);
    bool isEmptyTest = isEmptyQueue(testQueue);
    return dequeue(testQueue) == 100 && !isEmptyTest && !errorCode;
}

bool stackTest() {
    Stack * testStack = createStack();
    if (testStack == NULL) {
        return false;
    }
    int errorCode = 0;
    push(testStack, 200, &errorCode);
    bool isEmptyTest = isEmptyStack(testStack);
    return pop(testStack) == 200 && !isEmptyTest && !errorCode;
}

bool shuntingYardAlgorithmTest() {
    char * testString1 = "( 1 - 2) *(3+4)/ 5 ";
    char * testString2 = "9 / 10 - 11 ^ 12";
    Stack * testStack = createStack();
    Queue * testQueue = createQueue();
    if (testStack == NULL || testQueue == NULL) {
        return false;
    }
    int errorCode = 0;
    shuntingYardAlgorithm(testString1, testStack, testQueue, &errorCode);
    char * test1output = (char *) calloc(queueSize(testQueue), sizeof(char));
    if (test1output == NULL) {
        return false;
    }
    int testQueueSize = queueSize(testQueue);
    for (int i = 0; i < testQueueSize; ++i) {
        test1output[i] = dequeue(testQueue);
    }
    bool test1 = !strcmp(test1output, "1 2 - 3 4 + * 5 /");
    return !inputValidation(testString2) && test1;
}
