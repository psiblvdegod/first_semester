#include "tests.h"
#include <stdio.h>

bool test() {
    bool errorCode = false;
    Tree * tree = NULL;
    Node * node1 = createNode("111", 11, &errorCode);
    Node * node2 = createNode("000", 0, &errorCode);
    Node * node3 = createNode("333", 33, &errorCode);
    Node * node4 = createNode("444", 44, &errorCode);
    Node * node5 = createNode("222", 22, &errorCode);

    tree = createTree(node1, &errorCode);
    addNode(tree, node2, &errorCode);
    addNode(tree, node3, &errorCode);
    addNode(tree, node4, &errorCode);
    addNode(tree, node5, &errorCode);

    Node * parent = getNodeByKey(getRoot(tree), 2, &errorCode);

    disposeNode(tree, node3, &errorCode);
    printf("1");
}