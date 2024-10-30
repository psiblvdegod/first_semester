#include <stdio.h>
#include "stack.h"
#include "queue.h"
#include "tests.h"
#include "shuntingYardAlgorithm.h"

int main(void) {
    if (!stackTest() || !queueTest() || !shuntingYardAlgorithmTest()) {
        printf("Error. Tests failed.\n");
        return -1;
    }
    Stack * stack = createStack();
    Queue * queue = createQueue();
    if (stack == NULL || queue == NULL) {
        printf("Memory allocation error.\n");
        return -1;
    }
    char * infixNotation = "(666 - 777) * (888/999)";
    if (!inputValidation(infixNotation)) {
        printf("Error. Invalid value.\n");
        return -1;
    }
    int errorCode = 0;
    shuntingYardAlgorithm(infixNotation, stack, queue, &errorCode);
    printf("Infix notation: %s\nPostfix notation: ", infixNotation);
    while (!isEmptyQueue(queue)) {
        printf("%c", dequeue(queue));
    }
    printf("\n");
}
