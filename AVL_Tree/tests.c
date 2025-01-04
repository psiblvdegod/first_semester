#include "tests.h"
#include <stdio.h>
#include "errorCode.h"
#include <string.h>

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

int treeTests(const char *filePath) {
    int errorCode = NO_ERRORS;
    FILE *file = fopen(filePath, "r");
    if (file == nullptr) {
        return FILE_OPENING_ERROR;
    }
    Node *root = nullptr;
    while (!feof(file)) {
        char value[VALUE_MAX_SIZE] = {'0'};
        char key[VALUE_MAX_SIZE] = {'0'};
        fscanf(file, "%s%s", value, key);
        root = insert(root, );
    }
}
