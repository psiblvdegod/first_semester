#include "tests.h"
#include <stdio.h>

bool operationsWithTreeTest() {
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

    disposeNode(tree, node22, &errorCode);
    disposeNode(tree, node44, &errorCode);
    disposeNode(tree, node33, &errorCode);
    disposeNode(tree, node55, &errorCode);

    return getRoot(tree) == node11 && !errorCode;
}