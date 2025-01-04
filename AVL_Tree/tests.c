#include "tests.h"
#include "errorCode.h"
#include <string.h>

int treeTests() {
    int errorCode = NO_ERRORS;
    Node *root = NULL;
    bool isHeightChanged = false;
    root = insert(root, createNode("333", "333", &errorCode), &isHeightChanged);
    root = insert(root, createNode("444", "444", &errorCode), &isHeightChanged);
    root = insert(root, createNode("555", "555", &errorCode), &isHeightChanged);
    root = insert(root, createNode("000", "000", &errorCode), &isHeightChanged);
    root = insert(root, createNode("111", "111", &errorCode), &isHeightChanged);
    root = insert(root, createNode("555", "555", &errorCode), &isHeightChanged);
    root = insert(root, createNode("666", "666", &errorCode), &isHeightChanged);
    root = insert(root, createNode("AAA", "AAA", &errorCode), &isHeightChanged);
    root = insert(root, createNode("999", "999", &errorCode), &isHeightChanged);
    root = insert(root, createNode("777", "777", &errorCode), &isHeightChanged);
    root = insert(root, createNode("CCC", "CCC", &errorCode), &isHeightChanged);
    root = insert(root, createNode("EEE", "EEE", &errorCode), &isHeightChanged);
    root = insert(root, createNode("BBB", "BBB", &errorCode), &isHeightChanged);
    root = insert(root, createNode("DDD", "DDD", &errorCode), &isHeightChanged);

    int bp1 = 0;

    root = dispose(root, "333", &isHeightChanged);
    root = dispose(root, "AAA", &isHeightChanged);
    root = dispose(root, "BBB", &isHeightChanged);
    root = dispose(root, "111", &isHeightChanged);
    root = dispose(root, "222", &isHeightChanged);
    root = dispose(root, "EEE", &isHeightChanged);
    root = dispose(root, "555", &isHeightChanged);
    root = dispose(root, "444", &isHeightChanged);
    root = dispose(root, "777", &isHeightChanged);

    int bp2 = 0;
}

void test() {
    int errorCode = NO_ERRORS;
    Node *root = NULL;
    bool isHeightChanged = false;
    root = insert(root, createNode("111", "111", &errorCode), &isHeightChanged);
    root = insert(root, createNode("222", "222", &errorCode), &isHeightChanged);
    root = insert(root, createNode("333", "333", &errorCode), &isHeightChanged);
    root = insert(root, createNode("444", "444", &errorCode), &isHeightChanged);
    root = insert(root, createNode("555", "555", &errorCode), &isHeightChanged);
    root = dispose(root, "222", &isHeightChanged);
    root = dispose(root, "333", &isHeightChanged);
    int bp1 = 0;
}