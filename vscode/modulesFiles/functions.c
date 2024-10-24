#include "functions.h"

typedef struct StackElement {
    int value;
    struct StackElement * previous;
} StackElement;

struct Stack {
    StackElement * head;
};

Stack * createStack() {
    return (Stack *) calloc(1, sizeof(Stack));
}

void push(Stack * stack, int pushValue, int * errorCode) {
    StackElement * element = malloc(sizeof(StackElement));
    if (element == NULL) {
        *errorCode = 1;
        return;
    }
    element->value = pushValue;
    element->previous = stack->head;
    stack->head = element;
}

int pop(Stack * stack) {
    int value = stack->head->value;
    StackElement * temp = stack->head;
    stack->head = stack->head->previous;
    free(temp);
    return value;
}

int commonestElement(Stack * stack, int stackSize, int *errorCode) {
    if (stackSize < 0) {
        *errorCode = 1;
        return -1;
    }
    StackElement * searchForMaxMinValues = stack->head;
    int minElement = searchForMaxMinValues->value;
    int maxElement = searchForMaxMinValues->value;
    for (int i = 0; i < stackSize; ++i) {
        int foundValue = searchForMaxMinValues->value;
        minElement = foundValue < minElement ? foundValue : minElement;
        maxElement = foundValue > maxElement ? foundValue : maxElement;
        searchForMaxMinValues = searchForMaxMinValues->previous;
    }
    
    const int elementsRange = maxElement - minElement + 1;
    int* elementCounter = (int*) calloc(elementsRange, sizeof(int));
    if (elementCounter == NULL) {
        *errorCode = 1;
        return -1;
    }
    int result = 0, maxAmount = 0;
    StackElement * loopVariable = stack -> head;
    for (int i = 0; i < stackSize; ++i) {
        int valueIndex = loopVariable -> value - minElement; 
        ++elementCounter[valueIndex];
        if (elementCounter[valueIndex] > maxAmount) {
            maxAmount = elementCounter[valueIndex];
            result = loopVariable -> value;
        }
        loopVariable = loopVariable -> previous;
    }
    free(elementCounter);
    return result;
}

bool commonestElementTest() {
    int testArray[] = { -5, -5, 10, 10, 10, 10, 10, 10, -10, 5, 5, 5, 10, 10 };
    Stack * testStack = createStack();
    int stackSize = 14;
    int errorCode = 0;
    for (int i = 0; i < stackSize; ++i) {
        push(testStack, testArray[i], &errorCode);
        if (errorCode) {
            return 0;
        }
    }
    return commonestElement(testStack, stackSize, &errorCode) == 10 && !errorCode;
}

