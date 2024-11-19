#include "tests.h"
#include "parse.h"

bool treeTests() {
    bool errorCode = false;
    Node * node1 = createNode('*', &errorCode);
    Node * node2 = createNode(10, &errorCode);
    Node * node3 = createNode('+', &errorCode);
    Node * node4 = createNode(45, &errorCode);
    Node * node5 = createNode(55, &errorCode);

    Tree * tree = createTree(node1, &errorCode);
    addChild(node1, node2, left, &errorCode);
    addChild(node1, node3, right, &errorCode);
    addChild(node3, node4, left, &errorCode);
    addChild(node3, node5, right, &errorCode);

    if (getChild(node5, left) != NULL || getChild(node1, right) != node3) {
        return false;
    }
    if (getValue(node1, &errorCode) != '*' || getValue(node3, &errorCode) != '+') {
        return false;
    }
    if (getRoot(tree) != node1) {
        return false;
    }
    return !errorCode;
}
