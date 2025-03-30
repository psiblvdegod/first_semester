#include "treeTraversal.h"
#include "errorCode.h"
#include <stdio.h>

void fillQueueRecursive(Node *node, Queue *queue, int *errorCode) {
    if (node == nullptr) {
        return;
    }
    enqueue(queue, node, errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    fillQueueRecursive(getChild(node, left, errorCode), queue, errorCode);
    fillQueueRecursive(getChild(node, right, errorCode), queue, errorCode);
}

Queue *fillQueueWithTreeExpression(Node *root, int *errorCode) {
    if (root == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return nullptr;
    }
    Queue *queue = createQueue(errorCode);
    if (*errorCode != NO_ERRORS) {
        return nullptr;
    }
    fillQueueRecursive(root, queue, errorCode);
    if (*errorCode != NO_ERRORS) {
        deleteQueue(&queue, errorCode);
        return nullptr;
    }
    return queue;
}

void printTree(Node *node, int *errorCode) {
    if (node == nullptr) {
        return;
    }
    if (getChild(node, left, errorCode) == nullptr) {
        printf("%d ", getValue(node, errorCode));
    }
    else {
        printf("%c ", getValue(node, errorCode));
    }
    printTree(getChild(node, left, errorCode), errorCode);
    printTree(getChild(node, right, errorCode), errorCode);
}