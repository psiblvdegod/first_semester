#include "errorCode.h"
#include "tests.h"
#include "parse.h"
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
        deleteTree(&root, &errorCode);
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
    int expectedResult[] = {'*', 7, '-', 333, 444};

    const bool calculateTest = calculateTree(root, &errorCode) == 777;
    if (errorCode == NO_ERRORS && !calculateTest) {
        return TESTS_FAILED_ERROR;
    }
    return errorCode;
}