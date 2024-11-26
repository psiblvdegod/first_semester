#include "tests.h"
#include <string.h>

/*
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
*/

bool rotationTests() {
    bool errorCode = false;
    Node * node1 = createNode("a", "1", &errorCode);
    Node * node2 = createNode("b", "2", &errorCode);
    Node * node3 = createNode("c", "3", &errorCode);
    Node * node4 = createNode("d", "4", &errorCode);
    Node * node5 = createNode("e", "5", &errorCode);
    Node * node6 = createNode("f", "6", &errorCode);
    Node * node0 = createNode("0", "0", &errorCode);
    Node * node7 = createNode("g", "7", &errorCode);
    Node * node8 = createNode("h", "8", &errorCode);
    Node * node9 = createNode("i", "9", &errorCode);
    Node * node10 = createNode("j", "A", &errorCode);


    Node * node44 = createNode("dd", "4", &errorCode);

    Node * root = node8;
    root = insert(root, node9, &errorCode);
    errorCode = false;
    root = insert(root, node2, &errorCode);
    errorCode = false;
    root = insert(root, node1, &errorCode);
    errorCode = false;
    root = insert(root, node0, &errorCode);
    errorCode = false;
    root = insert(root, node4, &errorCode);
    errorCode = false;
    root = insert(root, node7, &errorCode);
    errorCode = false;
    root = insert(root, node10, &errorCode);
    errorCode = false;


    root = deleteNode(root, "8", &errorCode);
    root = deleteNode(root, "666", &errorCode);
    root = deleteNode(root, "2", &errorCode);
    root = deleteNode(root, "4", &errorCode);

    int a = 1-1;
}