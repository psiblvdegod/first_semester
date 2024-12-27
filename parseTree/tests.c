#include "tests.h"
#include "parse.h"
#include "errorCode.h"

void stackTests(int *errorCode) {
    Stack stack = NULL;
    push(&stack, createNode('1', errorCode), errorCode);
    push(&stack, createNode('2', errorCode), errorCode);
    push(&stack, createNode('3', errorCode), errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
}

void treeTests(int *errorCode) {
    Node *root = createNode('*', errorCode);;
    Node *node1 = createNode('+', errorCode);
    Node *node2 = createNode('-', errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    addChild(root, node1, left, errorCode);
    addChild(root, node2, right, errorCode);
    if (*errorCode != NO_ERRORS) {
        deleteTree(&root, errorCode);
        return;
    }
    const bool getChildTest = getChild(root, left, errorCode) == node1;
    const bool getValueTest = getValue(root, errorCode) == '*';
    const bool test = getChildTest && getValueTest;
    deleteTree(&root, errorCode);
    if (*errorCode == NO_ERRORS && !test) {
        *errorCode = TESTS_FAILED_ERROR;
    }
}