#include "tests.h"
#include <string.h>

bool treeTests() {
    bool errorCode = false;
    Node * node11 = createNode("111", 11, &errorCode);
    Node * node22 = createNode("222", 22, &errorCode);
    Node * node33 = createNode("333", 33, &errorCode);
    Node * node44 = createNode("444", 44, &errorCode);
    Node * node55 = createNode("555", 55, &errorCode);

    Tree * tree = createTree(node22, &errorCode);
    addNode(tree, node11, &errorCode);
    addNode(tree, node44, &errorCode);
    addNode(tree, node33, &errorCode);
    addNode(tree, node55, &errorCode);

    if (strcmp(getValue(node11, &errorCode), "111") != 0) {
        return false;
    }
    if (getKey(node22, &errorCode) != 22) {
        return false;
    }
    if (getParentByNode(tree, node33, &errorCode) != node44) {
        return false;
    }
    if (getNodeByKey(tree, 55, &errorCode) != node55) {
        return false;
    }
    if (findSuitablePosition(tree, 66, &errorCode) != node55) {
        return false;
    }

    disposeNode(tree, node22, &errorCode);
    disposeNode(tree, node44, &errorCode);
    disposeNode(tree, node33, &errorCode);
    disposeNode(tree, node55, &errorCode);

    return getRoot(tree) == node11 && !errorCode;
}
