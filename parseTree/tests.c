#include "treeTraversal.h"
#include "errorCode.h"
#include "tests.h"
#include "parse.h"
#include "queue.h"
#include <stdlib.h>

int stackTests() {
    int errorCode = NO_ERRORS;
    Stack stack = nullptr;
    push(&stack, createNode('1', &errorCode), &errorCode);
    push(&stack, createNode('2', &errorCode), &errorCode);
    push(&stack, createNode('3', &errorCode), &errorCode);
    const bool getTest1 = getValue(getHead(stack, &errorCode), &errorCode) == '3';
    pop(&stack, &errorCode);
    const bool getTest2 = getValue(getHead(stack, &errorCode), &errorCode) == '2';
    const bool test = getTest1 && getTest2;
    deleteStack(&stack, &errorCode);
    if (errorCode == NO_ERRORS && !test) {
        return TESTS_FAILED_ERROR;
    }
    return errorCode;
}

int treeTests() {
    int errorCode = NO_ERRORS;
    Node *root = createNode('*', &errorCode);;
    Node *node1 = createNode('+', &errorCode);
    Node *node2 = createNode('-', &errorCode);
    if (errorCode != NO_ERRORS) {
        free(root);
        free(node1);
        free(node2);
        return errorCode;
    }
    addChild(root, node1, left, &errorCode);
    addChild(root, node2, right, &errorCode);
    if (errorCode != NO_ERRORS) {
        free(root);
        free(node1);
        free(node2);
        return errorCode;
    }
    const bool getChildTest = getChild(root, left, &errorCode) == node1;
    const bool getValueTest = getValue(root, &errorCode) == '*';
    const bool test = getChildTest && getValueTest;
    deleteTree(&root, &errorCode);
    if (errorCode == NO_ERRORS && !test) {
        return TESTS_FAILED_ERROR;
    }
    return errorCode;
}

int queueTest() {
    int errorCode = NO_ERRORS;
    Queue *queue = createQueue(&errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    enqueue(queue, createNode(1, &errorCode), &errorCode);
    enqueue(queue, createNode(2, &errorCode), &errorCode);
    enqueue(queue, createNode(3, &errorCode), &errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    const bool test1 = getValue(dequeue(queue, &errorCode), &errorCode) == 1;
    const bool test2 = getValue(dequeue(queue, &errorCode), &errorCode) == 2;
    const bool test3 = getValue(dequeue(queue, &errorCode), &errorCode) == 3;
    deleteQueue(&queue, &errorCode);
    const bool test = test1 && test2 && test3;
    if (errorCode == NO_ERRORS && !test) {
        return TESTS_FAILED_ERROR;
    }
    return errorCode;
}

int treeTraversalTest() {
    int errorCode = NO_ERRORS;
    Node *root = createNode('*', &errorCode);;
    Node *node1 = createNode('+', &errorCode);
    Node *node2 = createNode('-', &errorCode);
    if (errorCode != NO_ERRORS) {
        free(root);
        free(node1);
        free(node2);
        return errorCode;
    }
    addChild(root, node1, left, &errorCode);
    addChild(root, node2, right, &errorCode);
    if (errorCode != NO_ERRORS) {
        free(root);
        free(node1);
        free(node2);
        return errorCode;
    }
    Queue *queue = fillQueueWithTreeExpression(root, &errorCode);
    int expectedResult[] = {'*', '+', '-'};
    for (size_t i = 0; !isEmptyQueue(queue, &errorCode); ++i) {
        if (getValue(dequeue(queue, &errorCode), &errorCode) != expectedResult[i]) {
            if (errorCode == NO_ERRORS) {
                errorCode = TESTS_FAILED_ERROR;
                break;
            }
        }
    }
    deleteQueue(&queue, &errorCode);
    return errorCode;
}

int parseTests(const char *filePath) {
    int errorCode = NO_ERRORS;
    FILE *file = fopen(filePath, "r");
    if (filePath == nullptr) {
        return FILE_OPENING_ERROR;
    }
    Node *root = buildTree(filePath, &errorCode);
    fclose(file);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    int expectedResult[] = {'*', 7, '-', -333, -444};
    Queue *queue = fillQueueWithTreeExpression(root, &errorCode);
    if (errorCode != NO_ERRORS) {
        deleteTree(&root, &errorCode);
        return errorCode;
    }
    for (size_t i = 0; !isEmptyQueue(queue, &errorCode); ++i) {
        if (getValue(dequeue(queue, &errorCode), &errorCode) != expectedResult[i]) {
            if (errorCode == NO_ERRORS) {
                errorCode = TESTS_FAILED_ERROR;
                break;
            }
        }
    }
    deleteQueue(&queue, &errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    const bool calculateTest = calculateTree(root, &errorCode) == -777;
    deleteTree(&root, &errorCode);
    if (errorCode == NO_ERRORS && !calculateTest) {
        return TESTS_FAILED_ERROR;
    }
    return errorCode;
}