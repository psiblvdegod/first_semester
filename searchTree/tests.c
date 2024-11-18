#include "tests.h"
#include <stdio.h>

bool test() {
    bool errorCode = false;
    Node * node11 = createNode("111", 11, &errorCode);
    Node * node33 = createNode("333", 33, &errorCode);
    Node * node44 = createNode("444", 44, &errorCode);
    Node * node22 = createNode("222", 22, &errorCode);
    Node * node25 = createNode("15", 25, &errorCode);


    Tree * tree = createTree(node11, &errorCode);
    addNode(tree, node33, &errorCode);
    addNode(tree, node44, &errorCode);
    addNode(tree, node22, &errorCode);
    addNode(tree, node25, &errorCode);

    //Node * parent = getParentByNode(tree, node1, &errorCode);

    disposeNode(tree, node33, &errorCode);
    disposeNode(tree, node25, &errorCode);
    disposeNode(tree, node44, &errorCode);
    printf("1");
}