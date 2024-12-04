#include "test.h"
#include "sorting.h"
#include "tree.h"
#include <string.h>

bool treeSortTests() {
    bool errorCode = false;
    Value array[] = {"eee", "bbb", "ddd", "ccc", "aaa"};
    const int arraySize = sizeof(array) / sizeof(Value);
    treeSort(array, arraySize, &errorCode);
    for (int i = 1; i < arraySize; ++i) {
        if (strcmp(array[i], array[i-1]) < 0) {
            return false;
        }
    }
    return !errorCode;
}

bool treeTests() {
    bool errorCode = false;
    Node * root = createNode("123", &errorCode);
    Node * leftChild = createNode("012", &errorCode);
    Node * rightChild = createNode("234", &errorCode);
    root = insert(root, leftChild);
    root = insert(root, rightChild);
    const bool test1 = getChild(root, left) == leftChild;
    const bool test2 = strcmp(getValue(rightChild), "234") == 0;
    return test1 && test2 && !errorCode;
}